#include "stdafx.h"
#include "MonitorProcess.h"
#include <iostream>
#include <chrono>
#include "Log.h"

MonitorProcess::MonitorProcess()
{
	log("");
}



MonitorProcess::~MonitorProcess()
{
	log("");
	stop();
}

void MonitorProcess::start(HANDLE processHandle, std::function<void(void)> processEndNotifier)
{
	log("");
	mProcessHandle = processHandle;
	mProcessEndNotifier = processEndNotifier;

	mThread = std::thread( [this] { runningThread(); } );
}

void MonitorProcess::stop() 
{
	log("");

	if (mThreadState == ThreadState::eRunning) {
		mThreadState = ThreadState::eStopping;
		log("");
		if (mThread.get_id() != std::this_thread::get_id()) {
			log("");
			if (mThread.joinable()) {
				log("");
				mThread.join();
			}
		} else {
			log("");
			while (mThreadState != ThreadState::eStopped) {
				log("");
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
			}
		}
	}

	if (mThread.joinable()) {
		log("");
		mThread.join();
	}

	log("thread stopped");
}

void MonitorProcess::terminateProcess()
{
	log("");
	TerminateProcess(mProcessHandle, 0);
}


void MonitorProcess::runningThread()
{
	log("");
	mThreadState = ThreadState::eRunning;
	DWORD dwExitCode;

	while (mThreadState == ThreadState::eRunning) {
		//log("");
		if (GetExitCodeProcess(mProcessHandle, &dwExitCode)) {
			//log("");
			if (dwExitCode == STILL_ACTIVE) {
				//still running
				std::this_thread::sleep_for(std::chrono::milliseconds(100) );
			}
			else {
				//not running anymore
				log("ended");
				mProcessEndNotifier();
				break;
			}
		}
		else {
			log("query failed, handle probably doesn't have the PROCESS_QUERY_INFORMATION access");
		}
	}

	log("");

	mThreadState = ThreadState::eStopped;
}
