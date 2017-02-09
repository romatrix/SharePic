#include "stdafx.h"
#include "PhotoViewer.h"
#include <functional>
#include "Log.h"


PhotoViewer::PhotoViewer()
{
}


PhotoViewer::~PhotoViewer()
{
}

void PhotoViewer::startViewer()
{
	log("");
	stopViewer();

	mExternalToolLauncher.reset(new ExternalToolLauncher(mExecutable,
		"\"" + mInitialPicture + "\"", std::bind(&PhotoViewer::onViewerEnd, this)));

	log("")
	mRunning = mExternalToolLauncher->launch();
	log("");
}

void PhotoViewer::stopViewer()
{
	log("");
	if (mRunning) {
		log("");
		mExternalToolLauncher->stop();
		log("");

		while (mRunning) {
			Sleep(10);
		}

		log("");
	}
}

void PhotoViewer::onViewerEnd()
{
	log("");
	mRunning = false;
}
