#pragma once

#include <string>
#include <windows.h>
#include <vector>

class DownloadedFileList
{
public:
	DownloadedFileList();
	~DownloadedFileList();


	void enumerateDirectory(const std::string& directory );
	void moveFiles(const std::string& destination );
	int getFileCount() { 
		return mFileList.size(); 
	}
	const std::string getFile(int index) {
		return mDirectory + "\\" + mFileList[index]; 
	}
private:
	std::vector<std::string> mFileList;
	std::string mDirectory;
};

