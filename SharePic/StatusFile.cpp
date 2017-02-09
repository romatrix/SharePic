#include "stdafx.h"
#include "StatusFile.h"
#include <Windows.h>
#include <vector>
#include <sstream>
#include "Log.h"

StatusFile::StatusFile(const string & filePath):mFilePath(filePath)
{
	log("");
}


StatusFile::~StatusFile()
{
	unlock();
	log("");
}

bool StatusFile::unlock() 
{
	log("");
	if (mFileHandle != INVALID_HANDLE_VALUE) {
		CloseHandle(mFileHandle);
		log("closing");
		mFileHandle = INVALID_HANDLE_VALUE;
		return true;
	}

	return false;
}

bool StatusFile::exist()
{
	DWORD dwAttrib = GetFileAttributes((LPSTR)mFilePath.c_str());

	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

bool StatusFile::lock()
{
	bool ret = false;
	mFileHandle = CreateFile((LPCSTR)mFilePath.c_str(), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE != mFileHandle) {
		ret = true;
	}

	log("file=" + mFilePath);
	mFileParser.parse(mFilePath);
	log("");

	return ret;
}

bool StatusFile::setLastSeenPicture(const string & lastViewedFile)
{
	bool ret = false;

	if (INVALID_HANDLE_VALUE != mFileHandle) {
		ret = true;

		mFileParser.set<string>("view", "last_seen", lastViewedFile);
	}

	return ret;
}

string StatusFile::getLastSeenPicture()
{
	string ret = mFileParser.get<string>("view", "last_seen");
	return ret;
}

bool StatusFile::clearDownloadAvailable()
{
	bool ret = false;

	if (INVALID_HANDLE_VALUE != mFileHandle) {
		ret = true;

		mFileParser.set<int>("download", "available", 0);
	}

	return ret;
}

bool StatusFile::serialize()
{
	if (INVALID_HANDLE_VALUE != mFileHandle) {
		log("");
		mFileParser.serialize(mFileHandle);
		return true;
	}

	return false;
}

bool StatusFile::getDownloadAvailable() 
{
	int ret = mFileParser.get<int>("download", "available");
	log("ret=" + mFileParser.get<string>("download", "available"));
	return ret != 0;
}


