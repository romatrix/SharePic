#include "stdafx.h"
#include "RemoteDirectory.h"

#pragma comment(lib, "mpr.lib")


RemoteDirectory::RemoteDirectory()
{
}


RemoteDirectory::~RemoteDirectory()
{
	if (mConnected) {
		DWORD retval = WNetCancelConnection2(mShare.c_str(), 0, TRUE);
	}
}

bool RemoteDirectory::connect(const string & share, const string &user, const string &password)
{
	mConnected = false;

	NETRESOURCE resource;
	resource.dwType = RESOURCETYPE_DISK;
	resource.lpLocalName = 0;
	resource.lpRemoteName = (LPSTR)share.c_str();
	resource.lpProvider = 0;
	DWORD conResult;
	DWORD result = WNetAddConnection2(&resource, user.c_str(), password.c_str(), CONNECT_TEMPORARY);
	//DWORD result = WNetAddConnection2(&resource, NULL, NULL, CONNECT_TEMPORARY);
	
	if (ERROR_ALREADY_ASSIGNED == result) {
		result = WNetAddConnection2(&resource, NULL, NULL, CONNECT_TEMPORARY);
	}

	if (result == NO_ERROR) {
		mShare = share;
		mConnected = true;
	}

	return mConnected;

	//NETRESOURCE resource;
	//resource.dwType = RESOURCETYPE_DISK;
	//resource.lpLocalName = 0;
	//resource.lpRemoteName = "\\\\25.110.150.185\\nela";
	//resource.lpProvider = 0;
	//DWORD conResult;
	////DWORD result = WNetAddConnection2(&resource, "bukann", "dudzik2", CONNECT_TEMPORARY);
	//DWORD result = WNetAddConnection2(&resource, NULL, NULL, CONNECT_TEMPORARY);
	//if (result == NO_ERROR) {
	//	// Go hog wild with files in \\server\share
	//	WIN32_FIND_DATA fd;
	//	CString searchpath = resource.lpRemoteName + CString("\\*.*");
	//	HANDLE findHandle = FindFirstFile(searchpath, &fd);
	//	if (findHandle != INVALID_HANDLE_VALUE) {
	//		// the rest of the enumeration here
	//		do {

	//			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	//			{

	//			}
	//			else
	//			{
	//				std::string s = fd.cFileName;

	//				s += " ";
	//			}
	//		} while (FindNextFile(findHandle, &fd) != 0);

	//		FindClose(findHandle);

	//		BOOL ret = CopyFile("C:\\Users\\rszul\\Pictures\\DSC_0011_poparwione.JPG", "\\\\25.110.150.185\\nela\\", FALSE);
	//		ret = ret;
	//	}

	//	DWORD retval = WNetCancelConnection2("\\\\25.110.150.185\\nela", 0, TRUE);
	//}
	//return false;
}

bool RemoteDirectory::synchronize(const string & localDirectory, function<void(const string&, int, bool)> callback)
{
	if (!mConnected) {
		return false;
	}

	//WIN32_FIND_DATA fd;

	//CString searchpath = localDirectory.c_str() + CString("\\*.*");

	//HANDLE findHandle = FindFirstFile(searchpath, &fd);
	//if (findHandle != INVALID_HANDLE_VALUE) {
	//	// the rest of the enumeration here
	//	do {

	//		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	//		{

	//		}
	//		else
	//		{
	//			std::string s = fd.cFileName;

	//			BOOL ret = CopyFile((LPSTR)(localDirectory + "\\" + string(fd.cFileName)).c_str(), mShare.c_str(), TRUE);
	//		}
	//	} while (FindNextFile(findHandle, &fd) != 0);

	//	FindClose(findHandle);

	//	return true;
	//	//BOOL ret = CopyFile("C:\\Users\\rszul\\Pictures\\DSC_0011_poparwione.JPG", "\\\\25.110.150.185\\nela\\", FALSE);
	//	//ret = ret;
	//}

	enumerateDirectory(localDirectory);

	for (int i = 0; i < mDirectoryContent.size(); ++i) {
		BOOL ret = CopyFile((LPSTR)mDirectoryContent[i].c_str(), mShare.c_str(), TRUE);

		if (callback) {
			int percent = mDirectoryContent.size() * 100 / i + 1;
			callback(mDirectoryContent[i], percent, ret);
		}
	}

	return false;
}

void RemoteDirectory::enumerateDirectory(const string & localDirectory)
{
	WIN32_FIND_DATA fd;

	CString searchpath = localDirectory.c_str() + CString("\\*.*");

	HANDLE findHandle = FindFirstFile(searchpath, &fd);
	if (findHandle != INVALID_HANDLE_VALUE) {
		// the rest of the enumeration here
		do {

			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{

			}
			else
			{
				std::string s = fd.cFileName;

				//BOOL ret = CopyFile((LPSTR)(localDirectory + "\\" + string(fd.cFileName)).c_str(), mShare.c_str(), TRUE);
				mDirectoryContent.push_back(localDirectory + "\\" + string(fd.cFileName));
			}
		} while (FindNextFile(findHandle, &fd) != 0);

		FindClose(findHandle);
	}

		//BOOL ret = CopyFile("C:\\Users\\rszul\\Pictures\\DSC_0011_poparwione.JPG", "\\\\25.110.150.185\\nela\\", FALSE);
		//ret = ret;
}
