
// SharePicDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SharePic.h"
#include "SharePicDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSharePicDlg dialog



CSharePicDlg::CSharePicDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SHAREPIC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSharePicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSharePicDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_WINDOWPOSCHANGING()
	ON_BN_CLICKED(IDCANCEL, &CSharePicDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CSharePicDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSharePicDlg message handlers

BOOL CSharePicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	mSharePicApp.init(AfxGetApp(), mTrayIconMessageId);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSharePicDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSharePicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



LRESULT CSharePicDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base 
	switch (message) {
		case WM_DESTROY:
			mSharePicApp.removeTrayIcon();
			break;
		case mTrayIconMessageId:
			switch (lParam)
			{
			case WM_LBUTTONUP:
				show(!mVisible);

				break;
			case WM_RBUTTONUP:
				CDialogEx::OnCancel();
				break;
			//case WM_CONTEXTMENU:
			//	ShowContextMenu();
			}
			break;
			break;
	}

	return CDialogEx::DefWindowProc(message, wParam, lParam);
}

void CSharePicDlg::show(bool set)
{
	mVisible = set;

	if (mVisible) {
		ShowWindow(SW_SHOW);
	}
	else {
		ShowWindow(SW_HIDE);
	}
}



void CSharePicDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	if (!mVisible) {
		lpwndpos->flags &= ~SWP_SHOWWINDOW;
	}

	CDialogEx::OnWindowPosChanging(lpwndpos);

	// TODO: Add your message handler code here
}


void CSharePicDlg::OnBnClickedCancel()
{
	show(false);
}


void CSharePicDlg::OnBnClickedOk()
{
	show(false);
}
