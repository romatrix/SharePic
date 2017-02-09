
#include "stdafx.h"
#include "DirectoryMonitor.h"
#include "Log.h"

DirectoryMonitor::DirectoryMonitor()
{
	log("");
}


DirectoryMonitor::~DirectoryMonitor()
{
	log("beg");
	if (mThread.joinable()) {
		log("set event");
		SetEvent(mStopHandle);
		log("join");
		mThread.join();
	}

	if (mStopHandle != INVALID_HANDLE_VALUE) {
		log("close stophandle");
		CloseHandle(mStopHandle);
	}

	if (mChangeHandle != INVALID_HANDLE_VALUE) {
		log("closing change handle");
		FindCloseChangeNotification(mChangeHandle);
		mChangeHandle = INVALID_HANDLE_VALUE;
	}

	log("end");
}


void DirectoryMonitor::start(const string & directory, function<void(void)> callback)
{
	mDirectory = directory;

	log("beg");

	mStopHandle = CreateEvent(nullptr, true, false, nullptr);

	log("");
	
	if (INVALID_HANDLE_VALUE == mStopHandle) {
		log("Could not start directory monitoring: CreateEvent");
		throw string("Could not start directory monitoring: CreateEvent");
	}

	log("");

	mChangeHandle = FindFirstChangeNotification(
		(LPSTR)mDirectory.c_str(),                         // directory to watch 
		FALSE,                         // do not watch subtree 
		/*FILE_NOTIFY_CHANGE_FILE_NAME*/FILE_NOTIFY_CHANGE_LAST_WRITE); // watch file name changes 

	log("");

	if (mChangeHandle == INVALID_HANDLE_VALUE)
	{
		log("Could not start directory monitoring: FindFirstChangeNotification");
		throw string("Could not start directory monitoring: FindFirstChangeNotification");
	}

	log("");

	mThread = thread([=]() { 
		log("calling threadMethod");
		threadMethod(callback);  
	});

	log("end");
}

void DirectoryMonitor::stop()
{
	if (mThread.joinable()) {
		SetEvent(mStopHandle);
		mThread.join();
	}
}

void DirectoryMonitor::threadMethod(function<void(void)> callback)
{
	HANDLE dwHandles[2];
	bool run = true;
	DWORD dwWaitStatus;

	dwHandles[0] = mStopHandle;
	dwHandles[1] = mChangeHandle;

	log("start");

	while (run) {
		dwWaitStatus = WaitForMultipleObjects(2, dwHandles,
			FALSE, INFINITE);

		switch (dwWaitStatus)
		{
		case WAIT_OBJECT_0:
			run = false;
			break;

		case WAIT_OBJECT_0 + 1:

			if (FindNextChangeNotification(dwHandles[1]) == FALSE)
			{
				log("ERROR: FindNextChangeNotification function failed");
			}
			else {
				try {
					log("callback");
					callback();
					log("after callback");
				}
				catch (...) {
					log("function fuck up");
				}
			}

			break;

		case WAIT_TIMEOUT:

			// A timeout occurred, this would happen if some value other 
			// than INFINITE is used in the Wait call and no changes occur.
			// In a single-threaded environment you might not want an
			// INFINITE wait.

			printf("\nNo changes in the timeout period.\n");
			break;

		default:
			printf("\n ERROR: Unhandled dwWaitStatus.\n");
			run = false;
			//ExitProcess(GetLastError());
			break;
		}
	}

	log("finishing");

	FindCloseChangeNotification(mChangeHandle);
	mChangeHandle = INVALID_HANDLE_VALUE;
	
	CloseHandle(mStopHandle);
	mStopHandle = INVALID_HANDLE_VALUE;

	log("end");
}
