
// SharePicDlg.h : header file
//

#pragma once

#include "Application.h"


// CSharePicDlg dialog
class CSharePicDlg : public CDialogEx
{
// Construction
public:
	CSharePicDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHAREPIC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	Application mSharePicApp;
	constexpr static uint32_t mTrayIconMessageId = WM_APP + 1;
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	bool mVisible = false;
	void show(bool set);
public:


	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonShowPictures();
};
