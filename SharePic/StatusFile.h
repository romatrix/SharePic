#pragma once

#include <string>
#include <Windows.h>
#include "SettingsParser.h"

using namespace std;

class StatusFile
{
public:
	enum class Status {
		Empty,
		PicturesAvailable,
		PicturesNotSeen,
		AllSeen
	};

	StatusFile(const string& filePath);
	~StatusFile();

	bool unlock();

	bool exist();

	bool lock();

	bool setLastSeenPicture(const string &lastViewedFile);
	string getLastSeenPicture();
	bool clearDownloadAvailable();
	bool serialize();
	bool getDownloadAvailable();
private:
	string mFilePath;
	HANDLE mFileHandle = INVALID_HANDLE_VALUE;
	SettingsParser mFileParser;
};

