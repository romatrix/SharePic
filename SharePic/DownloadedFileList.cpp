#include "stdafx.h"
#include "DownloadedFileList.h"
#include <map>


bool fileTimeComp(FILETIME lhs, FILETIME rhs) { return CompareFileTime(&lhs, &rhs) < 0; }

DownloadedFileList::DownloadedFileList()
{
}


DownloadedFileList::~DownloadedFileList()
{
}

void DownloadedFileList::enumerateDirectory(const std::string & directory)
{
	
	std::string dirContent = directory + std::string("\\*");

	WIN32_FIND_DATA ffd;
	HANDLE hFind = FindFirstFile(dirContent.c_str(), &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		throw std::string("FindFirstFile");
	}

	// List all the files in the directory with some info about them.
	std::multimap<FILETIME, std::string, bool(*)(FILETIME, FILETIME)> sortedFileList(&fileTimeComp);

	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{

		}
		else
		{
			sortedFileList.insert(std::pair<FILETIME, std::string>(ffd.ftLastWriteTime, ffd.cFileName));
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	for (const auto& i : sortedFileList) {
		mFileList.push_back(i.second);
	}

	mDirectory = directory;

}

void DownloadedFileList::moveFiles(const std::string & destination)
{
	for (const auto& i : mFileList) {
		std::string src(mDirectory + "\\" + i);
		std::string dst(destination + "\\" + i);

		BOOL ret = MoveFileEx(src.c_str(), dst.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH );
	}

	mDirectory = destination;
}
