#include <fstream>
#include <regex>
#include <iostream>

#include "stdafx.h"
#include "SettingsManager.h"



SettingsManager::SettingsManager()
{
}


SettingsManager::~SettingsManager()
{
}

void SettingsManager::load()
{
	std::ifstream f;

	f.open(mFile);

	std::string line;

	while (std::getline(f, line)) {

		std::smatch sm;
		//std::regex rgx = std::regex("\\s{4}([A-Za-z_0-9]+)\\s+(0x[0-9a-f]{8})\\s{3}Thumb Code\\s+([0-9]+).*");
		
		std::regex rgx = std::regex("#*([A-Za-z_]+)=([A-Za-z_0-9]+)");

		try {
			if (std::regex_match(line, sm, rgx)) {
				//mFunctions.push_back(FunctionCode(sm));
				std::string name = sm[1];
				std::string val = sm[2];

				for (auto const &i : mSearchStrings) {
					if (i.name == name) {
						(*this.*(i.method))(val);
					}
				}
			}
		}
		catch (std::regex_error &e) {
			std::cout << e.what() << " code=" << e.code() << '\n';
		}
	}
}

void SettingsManager::save()
{
}

void SettingsManager::parseViewer(const std::string &)
{
}

void SettingsManager::parseDirectory(const std::string &)
{
}
