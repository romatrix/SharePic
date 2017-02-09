#pragma once
#include <functional>
#include <string>
#include <vector>

using namespace std;



class RemoteDirectory
{
public:
	RemoteDirectory();
	~RemoteDirectory();

	bool connect(const string & share, const string & user, const string & password);
	bool RemoteDirectory::synchronize(const string & localDirectory, function<void(const string&, int, bool)> callback);
	

private:
	void enumerateDirectory(const string & localDirectory);
	string mShare;
	bool mConnected = false;
	vector<string> mDirectoryContent;

};

