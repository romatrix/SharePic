#pragma once
#include "SharePic.h"

class TaskbarNotificationHandler
{
public:
	TaskbarNotificationHandler();
	~TaskbarNotificationHandler();

	void addIcon(unsigned int messageId);
	void removeIcon();

	void setWinApp(CWinApp *winApp) { mWinApp = winApp; }

private:
	CWinApp *mWinApp = nullptr;
};

