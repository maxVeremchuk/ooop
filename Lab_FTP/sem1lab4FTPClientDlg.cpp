
// sem1lab4FTPClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sem1lab4FTPClient.h"
#include "sem1lab4FTPClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Csem1lab4FTPClientDlg dialog



Csem1lab4FTPClientDlg::Csem1lab4FTPClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SEM1LAB4FTPCLIENT_DIALOG, pParent)
{

//	listView = GetDlgItem(IDC_LIST1);
//	listView = getlist
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Csem1lab4FTPClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	ftp = new Myftp(&listView, _T("ftp://10.35.77.87/"), _T("q"), _T("q"), _T("C:\\Users\\mixon\\Desktop\\ftpClient\\"));
	database = new DB();
	database->createDB();
	//ftp = new Myftp();

	DDX_Control(pDX, IDC_LIST1, listView);
	DDX_Text(pDX, IDC_EDIT1, ftp->getUrl());
	DDX_Text(pDX, IDC_EDIT2, ftp->getUser());
	DDX_Text(pDX, IDC_EDIT3, ftp->getPass());
}

BEGIN_MESSAGE_MAP(Csem1lab4FTPClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Csem1lab4FTPClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CONNECT, &Csem1lab4FTPClientDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_BUTTON2, &Csem1lab4FTPClientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Csem1lab4FTPClientDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT1, &Csem1lab4FTPClientDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// Csem1lab4FTPClientDlg message handlers

BOOL Csem1lab4FTPClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	/*char *szColumn[2];

	szColumn[0] = "File names:";
	szColumn[1] = "Lenght:";

	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.fmt = LVCFMT_LEFT;

	for (int j = 0; j < 2; j++)
	{
		if (j == 0) lvc.cx = 200;
		else lvc.cx = 80;
		lvc.pszText = (LPWSTR)szColumn[j];
		if ((j == 1)) lvc.fmt = LVCFMT_RIGHT;
		lvc.iSubItem = j;
		listView->InsertColumn(j, &lvc);
	}*/
	CRect rect;
	listView.GetClientRect(&rect);
	int nColInterval = rect.Width() / 5;
	listView.InsertColumn(0, _T("File name:"), LVCFMT_LEFT, nColInterval * 4);
	listView.InsertColumn(1, _T("Length:"), LVCFMT_LEFT, nColInterval);

	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Csem1lab4FTPClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Csem1lab4FTPClientDlg::OnPaint()
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
HCURSOR Csem1lab4FTPClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Csem1lab4FTPClientDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void Csem1lab4FTPClientDlg::OnBnClickedConnect()
{

	BOOL flag = ftp->MyConnect();
	f = ftp->getFtpConn();
	if (flag == FALSE) return;
	printFiles();
}

void Csem1lab4FTPClientDlg::eraseList(void)
{
	for (int i = 0; i < numFiles; i++) { Leng[i] = ""; Files[i] = ""; }
	listView.DeleteAllItems();

	numFiles = 0;
	UpdateData(FALSE);
}

void Csem1lab4FTPClientDlg::printFiles(void)
{
	eraseList();
	ftp->setList(&listView);
	ftp->setFtpConn(f);
	//CFtpConnection *f = ftp->getFtpConn();
	numFiles = ftp->MyPrintFiles(Files, Leng);
	UpdateData(FALSE);
}


void Csem1lab4FTPClientDlg::OnBnClickedButton2()
{
	ftp->setFtpConn(f);
	ftp->onCopy();
	UpdateData(FALSE);
}


void Csem1lab4FTPClientDlg::OnBnClickedButton3()
{
	CT2CA pszConvertedUrl(ftp->getUrl());
	CT2CA pszConvertedUser(ftp->getUser());
	string coment = "coment";
	database->setData((string)pszConvertedUrl, (string)pszConvertedUser, coment);
}


void Csem1lab4FTPClientDlg::OnEnChangeEdit1()
{
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(str);
	ftp->setUrl(str);
}
