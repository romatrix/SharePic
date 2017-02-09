#include "stdafx.h"
#include "BakopHandler.h"

#include <functional>

#include <Windows.h>

BakopHandler::BakopHandler()
{
	char curDir[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, curDir);

	mCurDir = curDir;
}


BakopHandler::~BakopHandler()
{
}

void BakopHandler::cleanRemoteDirectory()
{
	std::string application = mCurDir + "\\WinSCP\\WinSCP.exe";
	std::string parameters = "/ini=nul /defaults /log=WinSCP.log /command \"open sftp://roman.szul:Backop12!@@host4.bakop.com/ "
		"-hostkey=\"\"ssh-rsa 2048 3c:d3:bc:af:15:6f:51:bd:6e:89:bd:ce:9b:60:0b:db\"\" "
		"-rawsettings FSProtocol=2\" \"synchronize remote -delete pusty /home/roman.szul/zdjecia\" \"exit\"\"";

	mWinSCPleanRemote.reset(new ExternalToolLauncher(application, parameters, bind(&BakopHandler::onRemoteCleanFinished, this)));

	mWinSCPleanRemote->launch();
}


void BakopHandler::downloadFiles()
{
	std::string application = mCurDir + "\\WinSCP\\WinSCP.exe";
	std::string parameters = "/ini=nul /defaults /log=WinSCP.log /command \"open sftp://roman.szul:Backop12!@@host4.bakop.com/ "
		"-hostkey=\"\"ssh-rsa 2048 3c:d3:bc:af:15:6f:51:bd:6e:89:bd:ce:9b:60:0b:db\"\" "
		"-rawsettings FSProtocol=2\" \"synchronize local zdjecia\\pobrane /home/roman.szul/zdjecia\" \"exit\"\"";

	mWinSCPDownload.reset(new ExternalToolLauncher(application, parameters, bind(&BakopHandler::onDownloadFinished, this)));

	mWinSCPDownload->launch();
}

void BakopHandler::uploadFiles()
{
	std::string application = mCurDir + "\\WinSCP\\WinSCP.exe";
	std::string parameters =	"/ini=nul /defaults /log=WinSCP.log /command \"open sftp://roman.szul:Backop12!@@host4.bakop.com/ "
							"-hostkey=\"\"ssh-rsa 2048 3c:d3:bc:af:15:6f:51:bd:6e:89:bd:ce:9b:60:0b:db\"\" "
							"-rawsettings FSProtocol=2\" \"synchronize remote zdjecia\\do_wyslania /home/roman.szul/zdjecia\" \"exit\"\"";

	mWinSCPUpload.reset(new ExternalToolLauncher(application, parameters, bind(&BakopHandler::onUploadFinished, this)));

	mWinSCPUpload->launch();
}

void BakopHandler::onDownloadFinished() {
	cleanRemoteDirectory();
	
	mFileList.enumerateDirectory(mCurDir + "\\zdjecia\\pobrane");
	mFileList.moveFiles("C:\\Users\\rszul\\Pictures\\zdjecia");
}

void BakopHandler::onRemoteCleanFinished() {
	MessageBox(nullptr, "Koniec", "synchronizacja", 0);
}

void BakopHandler::onUploadFinished()
{
	downloadFiles();
}
