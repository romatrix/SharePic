#include "stdafx.h"
#include "ExternalToolLauncher.h"
//#include <Shellapi.h>
#include <Windows.h>
#include "Log.h"


ExternalToolLauncher::ExternalToolLauncher(const string & application, const string & parameters, function<void(void)> callback): 
	mApplication(application), mParameters(parameters), mCallback(callback)
{
	log("");
}

ExternalToolLauncher::~ExternalToolLauncher()
{
	log("");
}

bool ExternalToolLauncher::launch()
{
	log("");

	string commandLine = mApplication + " " + mParameters;

	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	si.cb = sizeof(si);

	if (!CreateProcess(NULL,   // No module name (use command line)
		LPSTR(commandLine.c_str()),//tmp,       // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL, //startpath.c_str(), // Use given starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)          // Pointer to PROCESS_INFORMATION structure
		)
	{
		log("");
		return false;
	}

	mMonitorProcess.start(pi.hProcess, bind(&ExternalToolLauncher::onProcessEnd, this));
	log("");

	return true;
}

void ExternalToolLauncher::stop()
{
	log("");
	mMonitorProcess.terminateProcess();
}

void ExternalToolLauncher::onProcessEnd()
{
	log("");
	mCallback();
}
