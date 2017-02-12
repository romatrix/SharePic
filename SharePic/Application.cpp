#include <iostream>

#include "stdafx.h"
#include "Application.h"
#include "DownloadedFileList.h"
#include "StatusFile.h"
#include "log.h"

Application::Application()
{
	log("\n\n\nAPPLIACATION START\n\n\n");
}


Application::~Application()
{
	mPhotoViewer.stopViewer();
	log("\n\n\nAPPLIACATION END\n\n\n");
}

void Application::init(CWinApp *winApp, uint32_t tryIconMessageId)
{
	log("");

	try {
		mSettings.parse("settings.txt");

		mTaskbarArea.setWinApp(winApp);
		mTaskbarArea.addIcon(tryIconMessageId);

		string photoViewer = mSettings.get<string>("general", "picture_viewer");
		mPhotoViewer.setExecutable(photoViewer);

		startViewerWithLastSeenPicture();

		//check if status was changed offline
		scanDownloadFolder();

		string statusFolder = mSettings.get<string>("general", "status_folder");
		mDirecoryMonitor.start(statusFolder, bind(&Application::scanDownloadFolder, this));
	} catch(string &ex){
		log(string(ex));
	}
}

void Application::startViewerWithLastSeenPicture() 
{
	log("");

	string statusFolder = mSettings.get<string>("general", "status_folder");
	string statusFile = statusFolder + "\\" + mSettings.get<string>("general", "status_file");

	StatusFile sf(statusFile);

	sf.lock();


	try {

		string initialPicture = sf.getLastSeenPicture();

		mPhotoViewer.setInitialPicture(initialPicture);
		mPhotoViewer.startViewer();
	}
	catch (string &s) {
		log(s.c_str());
	}
}

void Application::removeTrayIcon()
{
	mTaskbarArea.removeIcon();
}

void Application::scanDownloadFolder()
{
	string statusFolder = mSettings.get<string>("general", "status_folder");
	string statusFile = statusFolder + "\\" + mSettings.get<string>("general", "status_file");

	for (int i = 0; i < 20; ++i) {

		StatusFile sf(statusFile);

		sf.lock();

		try {
			if (sf.getDownloadAvailable()) {
				DownloadedFileList dfl;

				string downloadFolder = mSettings.get<string>("general", "download_folder");
				dfl.enumerateDirectory(downloadFolder);

				if (dfl.getFileCount()) {
					string destinationFolder = mSettings.get<string>("general", "destination_folder");
					dfl.moveFiles(destinationFolder);

					string initialPicture = dfl.getFile(0);

					sf.setLastSeenPicture(initialPicture);

					mPhotoViewer.setInitialPicture(initialPicture);
					mPhotoViewer.startViewer();

				}
				else {
					//no files in download directory
				}

				sf.clearDownloadAvailable();
				sf.serialize();
				
			} 
		}
		catch (string &ex) {
			log(ex.c_str());
			Sleep(1000);
			continue;
		}

		break;
	}
}
