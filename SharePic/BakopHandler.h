#pragma once
#include <string>
#include <memory>

#include "ExternalToolLauncher.h"
#include "DownloadedFileList.h"

class BakopHandler
{
public:
	BakopHandler();
	~BakopHandler();

	void cleanRemoteDirectory();

	void setSynchronizeFolder(const std::string & folder) { mLocalFolder = folder; }

	void downloadFiles();
	void uploadFiles();
private:
	void onDownloadFinished();
	void onRemoteCleanFinished();
	void onUploadFinished();
private:
	std::string mLocalFolder;
	std::string mCurDir;
	std::unique_ptr<ExternalToolLauncher> mWinSCPUpload;
	std::unique_ptr<ExternalToolLauncher> mWinSCPDownload;
	std::unique_ptr<ExternalToolLauncher> mWinSCPleanRemote;
	DownloadedFileList mFileList;
};

