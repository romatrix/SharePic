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
	log("\n\n\nAPPLIACATION END\n\n\n");
}

void Application::init()
{
	try {
		mSettings.parse("settings.txt");

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
	string statusFolder = mSettings.get<string>("general", "status_folder");
	string statusFile = statusFolder + "\\" + mSettings.get<string>("general", "status_file");

	log("1");
	StatusFile sf(statusFile);
	log("2");

	sf.lock();


	try {

		log("3");
		string initialPicture = sf.getLastSeenPicture();

		log("4");
		mPhotoViewer.setInitialPicture(initialPicture);
		log("5");
		mPhotoViewer.startViewer();
		log("6");
	}
	catch (string &s) {
		log("startViewerWithLastSeenPicture");
		log(s.c_str());
	}

	log("7");
}

void Application::scanDownloadFolder()
{
	log("8");

	string statusFolder = mSettings.get<string>("general", "status_folder");
	log("9");
	string statusFile = statusFolder + "\\" + mSettings.get<string>("general", "status_file");

	log(__FUNCTION__);

	for (int i = 0; i < 20; ++i) {

		log("10");
		StatusFile sf(statusFile);

		sf.lock();
		log("11");

		try {
			if (sf.getDownloadAvailable()) {
				log("getDownloadAvailable");
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

					log("getFileCount");
				}
				else {
					//no files in download directory
				}

				sf.clearDownloadAvailable();
				sf.serialize();
				
				log("wyzerowany download");
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
