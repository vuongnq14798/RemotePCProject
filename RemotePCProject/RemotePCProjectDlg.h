
// RemotePCProjectDlg.h : header file
//

#pragma once
#include "RemotePC.h"

// CRemotePCProjectDlg dialog
class CRemotePCProjectDlg : public CDialogEx
{
// Construction
public:
	CRemotePCProjectDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REMOTEPCPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartprogram();
	afx_msg void OnBnClickedStopprogram();
	CRemotePC _remotePC;
	static UINT StartProgram(void* arg);
	void StartProgramThead();
	int m_port;
	CString m_ipAddress;
};
