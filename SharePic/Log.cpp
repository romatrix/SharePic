#include "stdafx.h"
#include <fstream>
#include "Log.h"



Log::Log(const string & log)
{
	ofstream of;

	of.open("log.txt", ios_base::app);

	of << log << '\n';

	of.close();
}

Log::Log(string &log)
{
	ofstream of;

	of.open("log.txt", ios_base::app);

	of << log << '\n';

	of.close();
}


Log::~Log()
{
}

Log& Log::operator()(const string & log)
{
	return *this;
}
