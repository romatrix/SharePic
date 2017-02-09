#pragma once

#include <string>
#include <vector>
#include <array>
#include <functional>
#include <map>

#include "SettingsParser.h"

using namespace std;

class SettingsManager
{
public:
	SettingsManager();
	~SettingsManager();

	void setPhotoViewer(const std::string & viewer) { mPhotoViewer = viewer;  }
	const std::string & getPhotoViewer() { return mPhotoViewer;  }

	void setPhotoDirectory(const std::string &photoDirectory) { mPhotoDirectory = photoDirectory; }
	const std::string & getPhotoDirectory() { return mPhotoDirectory; }

	void setCheckServerInterval(int checkServerInterval) { mCheckServerInterval = checkServerInterval; }
	int getCheckServerInterval() { return mCheckServerInterval; }

	void load();
	void save();

private:
	struct ParseMethod {
		std::string name;
		void (SettingsManager::*method)( const std::string& );
	};

	void parseViewer(const std::string&);
	void parseDirectory(const std::string&);
private:
	std::string mFile = "Settings.ini";
	std::string mPhotoViewer;
	std::string mPhotoDirectory;
	int mCheckServerInterval;
	std::array<ParseMethod, 2> mSearchStrings = {"Przegladarka", &SettingsManager::parseViewer};
	std::vector<uint32_t> mCheck;
	friend class SettingsParser;



};

