#pragma once

#include <string>
#include <memory>
#include "ExternalToolLauncher.h"

class PhotoViewer
{
public:
	PhotoViewer();
	~PhotoViewer();

	void setExecutable(const std::string &executable) { 
		mExecutable = executable;  
	}
	void setInitialPicture(const std::string &picture) { 
		mInitialPicture = picture;  
	}

	void startViewer();
    bool isRunning() { return mRunning; }

	void stopViewer();

private:
	void onViewerEnd();
private:
	bool mRunning = false;
	std::string mExecutable;
	std::string mInitialPicture;
	std::unique_ptr<ExternalToolLauncher> mExternalToolLauncher;
};

