#include "stdafx.h"
#include "ftpClient.h"
#include <string>
using namespace std;


BOOL Myftp::MyConnect()
{
	CString _url = MyGetURL();
	CString path = MyGetPath();
	if (ConnFlag == TRUE) MyEndConnect();
	try
	{
		if ((user == "anonymous") || (user == ""))
			ftpConnection = internetSession.GetFtpConnection(_url, NULL, NULL, nPort, FALSE);
		else
			ftpConnection = internetSession.GetFtpConnection(_url, user, pass, nPort, FALSE);

		ftpConnection->SetCurrentDirectory(path);
		ConnFlag = TRUE;
		listView->SetFocus();
		return TRUE;
	}
	catch (CInternetException* pException)
	{
		pException->ReportError();
		return FALSE;
	}

}

CString Myftp::MyGetPath()
{
	char *pre = new char[url.GetLength()];
	char *first = new char[7];
	char *ftp = "ftp://";
	char sl = '/';
	CString null;
	int len, num;
	int i;

	len = url.GetLength();

	if (len <= 5)
	{
		num = -1; pre = "";
		for (int i = 0; i < len; i++) if (char(url.GetAt(i)) == sl) { num = i; i = len - 1; }
		if ((char(url.GetAt(num + 1)) == 0) || num < 0) { return CString("/"); }

		for (i = (num); i < len; i++)
			pre[i - num] = (char)url.GetAt(i);
		pre[len - num] = 0;

		return (CString)&pre[0];
	}

	for (i = 0; i<6; i++) first[i] = (char)url.GetAt(i);
	first[6] = 0;

	if ((strcmp(first, ftp) == 0) && (len == 6)) { MessageBeep(65535); return null; }

	if (strcmp(first, ftp) == 0)
	{
		num = -1; pre = "";
		for (int i = 6; i < len; i++) if (char(url.GetAt(i)) == sl) { num = i; i = len - 1; }
		if ((char(url.GetAt(num + 1)) == 0) || num < 0) { return (CString)"/"; }

		for (i = (num); i < len; i++) {
			pre[i - num] = (char)url.GetAt(i);
		}

		pre[len - num] = 0;

		return (CString)&pre[0];
	}

	if (strcmp(first, ftp) == 1)
	{
		num = -1; pre = "";
		for (int i = 0; i < len; i++) if (char(url.GetAt(i)) == sl) { num = i; i = len - 1; }
		if ((char(url.GetAt(num + 1)) == 0) || num < 0) { return (CString)"/"; }

		for (i = (num); i < len; i++)
			pre[i - num] = (char)url.GetAt(i);
		pre[len - num] = 0;
		return (CString)&pre[0];
	}

	return null;
}

CString Myftp::MyGetURL()
{
	char *pre = new char[url.GetLength()];
	char *first = new char[6];
	char *ftp = "ftp://";
	char sl = '/';
	int len;
	CString null;

	len = url.GetLength();

	if (len <= 5)
	{
		for (int i = 0; i < len; i++)
		{
			if (char(url.GetAt(i)) != sl)
				pre[i] = (char)url.GetAt(i);
			else { pre[i] = 0;  return (CString)&pre[0]; }
		}
	}

	for (int i = 0; i<6; i++) first[i] = (char)url.GetAt(i);
	first[6] = 0;

	if ((strcmp(first, ftp) == 0) && (len == 6)) { return null; }
	int i;
	if (strcmp(first, ftp) == 0)
	{
		for (i = 6; i < len; i++)
		{
			if (char(url.GetAt(i)) != sl)
				pre[i - 6] = (char)url.GetAt(i);
			else { pre[i - 6] = 0; i = (len - 1); }
		}
		return (CString)&pre[0];

	}

	if (strcmp(first, ftp) == 1)
	{
		for (i = 0; i < len; i++)
		{
			if (char(url.GetAt(i)) != sl)
				pre[i] = (char)url.GetAt(i);
			else { pre[i] = 0; i = (len - 1); }
		}
		return (CString)&pre[0];
	}

	return null;
}

void Myftp::MyEndConnect()
{
	delete ftpConnection;
	ConnFlag = FALSE;
}

int Myftp::MyPrintFiles(char **Files, char **Leng)
{
	//ftpConnection = internetSession.GetFtpConnection(MyGetURL(), user, pass, nPort, FALSE);
	ftpConnection->GetCurrentDirectory(curDirectory);
	CFtpFileFind ftpFileFind(ftpConnection);
	ftpFileFind.FindFile();

	temp = "Current directory = ";
	temp += curDirectory;

	int x = 1;
	int len = 0;
	CTime tim;
	LV_ITEM lvi;

	lvi.mask = LVIF_TEXT | LVIF_IMAGE;
	lvi.iSubItem = 0;

	Files[0] = ".."; Leng[0] = "-";
	listView->SetTextColor(RGB(150, 0, 0));
	lvi.iItem = 0;
	
	wchar_t wtext[20];
	mbstowcs(wtext, Files[0], strlen(Files[0]) + 1);
	LPWSTR filesPtr = wtext;
	lvi.pszText = filesPtr;

	lvi.cchTextMax = 0;
	lvi.iImage = 0;
	listView->InsertItem(&lvi);


	mbstowcs(wtext, Leng[0], strlen(Leng[0]) + 1);
	LPWSTR lengPtr = wtext;

	listView->SetItemText(0, 1, lengPtr);


	do
	{
		temp = "";

		len = 0;

		gotFile = ftpFileFind.FindNextFile();

		temp = (CString)ftpFileFind.GetFileName();

		len = temp.GetLength();
		temp2 = new char[len];
		for (int a = 0; a < len; a++) { temp2[a] = (char)temp.GetAt(a); }
		temp2[len] = 0;
		Files[x] = temp2;

		if (ftpFileFind.IsDirectory())
		{
			Leng[x] = "<Dir>";

		}
		else
		{
			_itoa_s((int)ftpFileFind.GetLength(), temp3, 10);
			Leng[x] = temp3;

		}

		lvi.iItem = x;
		mbstowcs(wtext, Files[x], strlen(Files[x]) + 1);
		filesPtr = wtext;
		lvi.pszText = filesPtr;


		lvi.cchTextMax = x;
		lvi.iImage = x;
		listView->InsertItem(&lvi);

		mbstowcs(wtext, Leng[x], strlen(Leng[x]) + 1);
		 lengPtr = wtext;

		listView->SetItemText(x, 1, lengPtr);


		++x;
	} while ((x<NUM) && (gotFile));

	listView->SetFocus();
	listView->SetHotItem(0);


	listView->UpdateData(FALSE);
	return x;
	//m_enter->EnableWindow(TRUE);
	//UpdateData(FALSE);
}

BOOL Myftp::onCopy()
{
	POSITION cur_pos;
	int flag_pos;
	int count = 0;
	CString file, len;
	CString new_url, dir;
	int Sel_files[NUM];
	TCHAR szBuff[64];

	string m_edit;
	char temp3[100];
	m_edit = "";
	cur_pos = listView->GetFirstSelectedItemPosition();

	if ((int)cur_pos <= 1) { 
		
		
		HWND hWnd = ::GetConsoleWindow();
		_stprintf(szBuff, _T("No selected file(s)"), hWnd);
		MessageBox(NULL, szBuff, L"Error", MB_OK); return FALSE;
	};

	len = listView->GetItemText((int)cur_pos - 1, 1);
	if (len != "<Dir>") { Sel_files[0] = (int)cur_pos - 1; count++; }

	_itoa_s((int)cur_pos - 1, temp3, 10);
	m_edit +="start = ";
	m_edit += &temp3[0];
	m_edit += "\r\n";
	do
	{
		flag_pos = listView->GetNextSelectedItem(cur_pos);
		_itoa_s((int)cur_pos - 1, temp3, 10);
		m_edit += "next = "; m_edit += &temp3[0]; m_edit += "\r\n";

		len = listView->GetItemText((int)cur_pos - 1, 1);
		if (len != "<Dir>") { Sel_files[count++] = (int)cur_pos - 1; }

	} while ((int)cur_pos >= 1);
	count--;
	_itoa_s(count, temp3, 10);
	m_edit += " Selected files = "; m_edit += &temp3[0]; m_edit += "\r\n"; m_edit += "\r\n";
	if (count == 0) {
		HWND hWnd = ::GetConsoleWindow();
		_stprintf(szBuff, _T("No selected file(s)"), hWnd);
		MessageBox(NULL, szBuff, L"Error", MB_OK); return FALSE;
	};


	for (int i = 0; i <= (count - 1); i++)
	{
		len = listView->GetItemText(Sel_files[i], 1);
		file = listView->GetItemText(Sel_files[i], 0);
		
		CT2CA pszConvertedFile(file);
		CT2CA pszConvertedLen(len);

		m_edit += "Copy file = "; m_edit += pszConvertedFile; m_edit += "  len = "; m_edit += pszConvertedLen; m_edit += "\r\n";

		int down = ftpConnection->GetFile(file, save + file, FALSE);


		if (down == 0)
		{
			MessageBeep(65535);
			m_edit += "Error save file. Not create directory !!!";
			listView->SetFocus();
			return FALSE;
		}

	}

	listView->SetFocus();
	return TRUE;
}