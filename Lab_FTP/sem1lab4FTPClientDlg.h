
// sem1lab4FTPClientDlg.h : header file
//

#pragma once
#include "ftpClient.h"
#include "dataBase.h"

#define NUM 1000

// Csem1lab4FTPClientDlg dialog
class Csem1lab4FTPClientDlg : public CDialogEx
{
// Construction
public:
	Csem1lab4FTPClientDlg(CWnd* pParent = NULL);	// standard constructor
	void eraseList(void);
	void printFiles(void);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEM1LAB4FTPCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	
// Implementation
protected:
	HICON m_hIcon;
	Myftp *ftp;
	DB *database;
	CFtpConnection *f;
	CListCtrl listView;

	char *Files[NUM];
	char *Leng[NUM];
	unsigned long fileLengths[NUM];
	int numFiles;
	char *temp3;


	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit1();
};
