
// SharePic.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SharePic.h"
#include "SharePicDlg.h"

//#include "ExternalToolLauncher.h"
#include "BakopHandler.h"
#include "DownloadedFileList.h"
#include "PhotoViewer.h"
#include "SettingsParser.h"
#include "DirectoryMonitor.h"
#include "Application.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSharePicApp

BEGIN_MESSAGE_MAP(CSharePicApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


class test {
public:
	void t1() {
		int m = 0;
		m++;
	}
	int k = 0;
};

// CSharePicApp construction

//BakopHandler bh;
//PhotoViewer pv;
//DirectoryMonitor dm;

void dupa()
{
	NETRESOURCE resource;
	resource.dwType = RESOURCETYPE_DISK;
	resource.lpLocalName = 0;
	resource.lpRemoteName = "\\\\25.110.150.185\\nela";
	resource.lpProvider = 0;
	DWORD conResult;
	//DWORD result = WNetAddConnection2(&resource, "bukann", "dudzik2", CONNECT_TEMPORARY);
	DWORD result = WNetAddConnection2(&resource, NULL, NULL, CONNECT_TEMPORARY);
	if (result == NO_ERROR) {
		// Go hog wild with files in \\server\share
		WIN32_FIND_DATA fd;
		CString searchpath = resource.lpRemoteName + CString("\\*.*");
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

					s += " ";
				}
			} while (FindNextFile(findHandle, &fd) != 0);

			FindClose(findHandle);

			BOOL ret = CopyFile("C:\\Users\\rszul\\Pictures\\DSC_0011_poparwione.JPG", "\\\\25.110.150.185\\nela\\", FALSE);
			ret = ret;
		}

		DWORD retval = WNetCancelConnection2("\\\\25.110.150.185\\nela", 0, TRUE);
	}

	
}

//void settings() {
//	SettingsParser sp;
//
//	sp.parse("settings.txt");
//
//	int m = sp.get<int>("general", "x");
//	std::string s = sp.get<std::string>("general", "y");
//
//	int k = 0;
//}
//
//void picuturesDownloaded() {
//
//}
//
//void monitor() {
//	dm.start("C:\\projekty\\slideshow\\SharePic\\zdjecia\\pobrane\\status", picuturesDownloaded);
//
//	Sleep(30000);
//
//	dm.stop();
//}



CSharePicApp::CSharePicApp()
{
	//settings();
	//monitor();
	//dupa();
	//test t;
	//
	//ExternalToolLauncher etl("\"C:\\Program Files (x86)\\Google\\Picasa3\\PicasaPhotoViewer.exe\"", 
	//	"\"C:\\Users\\rszul\\Pictures\\fotka_portal.jpg\"", 
	//	bind(&test::t1, &t));
	//
	//t.k = 1;
	//etl.Launch();

	//bh.uploadFiles();
	//bh.cleanRemoteDirectory();
	//DownloadedFileList dfl;

	////dfl.enumerateDirectory("C:\\Users\\rszul\\Pictures\\sylwester_2016");
	//dfl.enumerateDirectory("C:\\projekty\\slideshow\\SharePic\\zdjecia\\pobrane");

	//if (dfl.getFileCount()) {
	//	dfl.moveFiles("C:\\Users\\rszul\\Pictures\\zdjecia");

	//	pv.setInitialPicture(dfl.getFile(0));
	//	pv.startViewer();
	//}
	
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CSharePicApp object

CSharePicApp theApp;


// CSharePicApp initialization

BOOL CSharePicApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CSharePicDlg dlg;

	//dlg.Create(IDD_SHAREPIC_DIALOG);
	
	m_pMainWnd = &dlg;
	//dlg.ShowWindow(SW_SHOW);
	//CWinApp::Run();

	//return TRUE;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	//// Delete the shell manager created above.
	//if (pShellManager != NULL)
	//{
	//	delete pShellManager;
	//}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}



int CSharePicApp::Run()
{
	// TODO: Add your specialized code here and/or call the base class

	return CWinApp::Run();
}
