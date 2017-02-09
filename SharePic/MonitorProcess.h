#include <Windows.h>
#include <thread>
#include <functional>

#pragma once
class MonitorProcess
{
public:
	enum class ThreadState
	{
		eRunning,
		eStopping,
		eStopped
	};
public:
	MonitorProcess();
	~MonitorProcess();

	void start(HANDLE processHandle, std::function<void(void)> processEndNotifier);
	void stop();
	void terminateProcess();
private:
	void runningThread();
private:
	HANDLE mProcessHandle = nullptr;
	std::thread mThread;
	volatile ThreadState mThreadState = ThreadState::eStopped;
	std::function<void(void)> mProcessEndNotifier;

};

