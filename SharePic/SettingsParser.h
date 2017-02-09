#pragma once

#include <string>
#include <map>
#include <sstream>

using namespace std;

template <class T> class Parser{
public:
	T get(const string &val) {
		T ret = val;
		return ret;
	}

	string set(T val) {
		T ret = val;
		return ret;
	}
};

template<> class Parser<int> {
public:
	int get(const string &val) {
		stringstream s(val);
		TRACE("%s val=%s", __FUNCTION__, val.c_str());
		int ret;
		s >> ret;
		return ret;
	}

	string set(int val) {
		stringstream s;
		s << val;

		return s.str();
	}
};

class SettingsParser
{
public:
	friend class Parser<int>;
	friend class Parser<string>;

	SettingsParser()=default;
	~SettingsParser()=default;

	struct Section {
		Section() = default;
		virtual void parse(const string& line);

		map<string, string> mVars;
	};

	template <class T> T get(const string& section, const string& var)
	{
		Parser<T> p;
		T ret;
		Section *s = &mSections[section];
		if (s) {
			string v = s->mVars[var];

			if (v.size()) {
				ret = p.get(v);
			} else {
				throw string("no such variable:[" + section + "]:" + var);
			}
		}

		return ret;
	}

	template <class T> void set(const string& section, const string& var,  T value)
	{
		Parser<T> p;

		Section *s = &mSections[section];
		if (s) {
			s->mVars[var] = p.set(value);
		}else {
			mSections[section] = move(Section());
			mSections[section].mVars[var] = p.set(value);
		}
	}

	void parse(const string &file);
	void serialize();
	void serialize(HANDLE fileHandle);

private:
	map<string, Section> mSections;
	string mFilePath;

	
};

