#pragma once

#include "SettingsParser.h"
#include "DirectoryMonitor.h"
#include "PhotoViewer.h"
#include "SharePic.h"
#include "TaskbarNotificationHandler.h"

using namespace std;

class Application
{
public:
	Application();
	~Application();

	void init(CWinApp *winApp, uint32_t tryIconMessageId);
	void startViewerWithLastSeenPicture();

	void removeTrayIcon();
private:
	void scanDownloadFolder();

	SettingsParser mSettings;
	DirectoryMonitor mDirecoryMonitor;
	PhotoViewer mPhotoViewer;
	TaskbarNotificationHandler mTaskbarArea;
};

