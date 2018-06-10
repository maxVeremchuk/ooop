#pragma once
#include "stdafx.h"
#include <AFXODLGS.H>
#include <afxinet.h>

#define NUM 1000

class Myftp
{
public:
	Myftp(CListCtrl *_listView, CString _url, CString _user, CString _pass, CString _save)
	{
		url = _url;
		pass = _pass;
		user = _user;
		save = _save;
		listView = _listView;
		//MyConnect(MyGetURL(), MyGetPath());
	}
	void MyEndConnect(void);

	int MyPrintFiles(char **Files, char **Leng);
	BOOL MyConnect();
	BOOL onCopy();
	CString MyGetPath();
	CString MyGetURL();
	CString getUrl()
	{
		return url;
	}
	CString getUser()
	{
		return user;
	}
	CString getPass()
	{
		return pass;
	}
	void setUrl(CString val)
	{
		url = val;
	}
	void setUser(CString val)
	{
		user = val;
	}
	void setPass(CString val)
	{
		pass = val;
	}
	void setList(CListCtrl *_list)
	{
		listView = _list;
	}
	CFtpConnection *getFtpConn()
	{
		return ftpConnection;
	}
	void setFtpConn(CFtpConnection * f)
	{
		 ftpConnection = f;
	}
	
private:
	CString	url;
	CString	user;
	CString	pass;
	CString save;
	CListCtrl *listView;

	CString curDirectory;

	INTERNET_PORT nPort = 21;
	CString temp;
	char *temp2;
	char temp3[100];
	CInternetSession internetSession;
	CFtpConnection *ftpConnection;
	BOOLEAN gotFile;
	BOOL ConnFlag = FALSE;
};