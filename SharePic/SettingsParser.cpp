#include "stdafx.h"
#include <fstream>
#include <regex>
#include <iostream>
#include <fstream>

#include "SettingsParser.h"


void SettingsParser::parse(const string & file)
{
	ifstream f;

	mFilePath = file;
	f.open(file);

	string line;
	Section *s = nullptr;
	
	while (getline(f, line)) {
		regex r("(\\[)([a-zA-Z]+)(\\])", regex::ECMAScript);
		smatch m;

		if (regex_match(line,m, r)) {
			cout << m[2] << '\n';
			mSections[m[2]] = move(Section());
			s = &mSections[m[2]];
		} else {
			if (s) {
				s->parse(line);
			}
		}
	}

	f.close();
}

void SettingsParser::serialize()
{
	stringstream ss;

	for_each(mSections.begin(), mSections.end(), [&](const auto &p) {
		ss << '[' << p.first << "]\n";
		
		for (const auto &v : p.second.mVars) {
			ss << v.first << '=' << v.second << '\n';
		}
	});

	ofstream file;

	file.open(mFilePath);

	bool ret = file.fail();
	file << ss.str();
	file.close();
}

void SettingsParser::serialize(HANDLE fileHandle)
{
	stringstream ss;

	for_each(mSections.begin(), mSections.end(), [&](const auto &p) {
		ss << '[' << p.first << "]\n";

		for (const auto &v : p.second.mVars) {
			ss << v.first << '=' << v.second << '\n';
		}

		ss << "\n";
	});

	string fileContent = ss.str();

	TRACE("%s status=%s", __FUNCTION__, fileContent.c_str());

	DWORD written = 0;

	SetFilePointer(fileHandle, 0, nullptr, FILE_BEGIN);

	if (!SetEndOfFile(fileHandle)) {
		throw string("Could not truncate file ");
	}

	if (!WriteFile(fileHandle, fileContent.c_str(), fileContent.size(), &written, nullptr)) {
		throw string("Could not write to file");
	}
}



void SettingsParser::Section::parse(const string & line)
{
	regex r("([a-zA-Z_]+)=([a-zA-Z\"\\\\_0-9\\(\\) \\.:]+)");
	smatch m;

	if (regex_match(line, m, r)) {
		cout << m[1] << '\n';
		mVars[m[1]] = m[2];
	}
}
