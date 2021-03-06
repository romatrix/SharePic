#pragma once
#include <string>
#include <sstream>

using namespace std;

class Log
{
public:
	Log(const string & log);
	Log(string &log);
	Log() = default;
	~Log();
public:
	Log& operator()(const string &log);
};

#ifdef _DEBUG
	#define log(x){ \
		stringstream ss; \
		ss << '[' << this << "][" << __FUNCTION__ << ':' <<__LINE__ << "] " << x; \
		Log(ss.str()); \
}
#else
	#define log(x)
#endif

