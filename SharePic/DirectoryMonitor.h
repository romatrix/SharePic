#pragma once

#include <thread>
#include <string>
#include <windows.h>
#include <functional>

using namespace std;

class DirectoryMonitor
{
public:
	DirectoryMonitor();
	~DirectoryMonitor();

	void start(const string & directory, function<void(void)> callback);
	void stop();
private:
	void threadMethod(function<void(void)>);
	string mDirectory;
	thread mThread;
	HANDLE mStopHandle = INVALID_HANDLE_VALUE;
	HANDLE mChangeHandle = INVALID_HANDLE_VALUE;
};

