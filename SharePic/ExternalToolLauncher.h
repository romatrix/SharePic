#pragma once

#include <string>
#include <functional>
#include "MonitorProcess.h"

using namespace std;

class ExternalToolLauncher
{
public:
	ExternalToolLauncher(const string& application, const string& parameters, function<void (void)> callback);
	~ExternalToolLauncher();

	bool launch();
	void stop();
private:
	void onProcessEnd();
private:
	function<void(void)> mCallback;
	const string mApplication;
	const string mParameters;
	MonitorProcess mMonitorProcess;
};

