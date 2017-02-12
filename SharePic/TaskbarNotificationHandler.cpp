#include "stdafx.h"
#include "TaskbarNotificationHandler.h"
#include <Windows.h>
#include "Resource.h"
#include "log.h"


TaskbarNotificationHandler::TaskbarNotificationHandler()
{
	log("");
}


TaskbarNotificationHandler::~TaskbarNotificationHandler()
{
	log("");
}

void TaskbarNotificationHandler::addIcon(unsigned int messageId)
{
	log("");

	NOTIFYICONDATA nid = {};
	nid.cbSize = sizeof(nid);
	nid.hWnd = mWinApp->m_pMainWnd->GetSafeHwnd();
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;

	strcpy(nid.szTip, "Test application");

	nid.hIcon = (HICON)LoadImage(mWinApp->m_hInstance,
		MAKEINTRESOURCE(IDR_MAINFRAME),
		IMAGE_ICON,
		GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CYSMICON),
		LR_DEFAULTCOLOR);

	nid.uCallbackMessage = messageId;


	// Show the notification.
	if (Shell_NotifyIcon(NIM_ADD, &nid)) {
		log("OK");
	}
	else {
		log("FAIL");
	}
}

void TaskbarNotificationHandler::removeIcon()
{
	log("");

	NOTIFYICONDATA nid = {};
	nid.cbSize = sizeof(nid);
	nid.hWnd = mWinApp->m_pMainWnd->GetSafeHwnd();
	nid.uFlags = NIF_ICON;


	nid.hIcon = (HICON)LoadImage(mWinApp->m_hInstance,
		MAKEINTRESOURCE(IDR_MAINFRAME),
		IMAGE_ICON,
		GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CYSMICON),
		LR_DEFAULTCOLOR);


	// Show the notification.
	if (Shell_NotifyIcon(NIM_DELETE, &nid)) {
		log("OK");
	}
	else {
		log("FAIL");
	}
}
