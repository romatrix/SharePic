#pragma once

#include "SettingsParser.h"
#include "DirectoryMonitor.h"
#include "PhotoViewer.h"

using namespace std;

class Application
{
public:
	Application();
	~Application();

	void init();
	void startViewerWithLastSeenPicture();
private:
	void scanDownloadFolder();

	SettingsParser mSettings;
	DirectoryMonitor mDirecoryMonitor;
	PhotoViewer mPhotoViewer;
};

