#pragma once

#include <assert.h>
#include "ftpClient.h"
#include "dataBase.h"
#include "sem1lab4FTPClient.h"
void unitTestDB()
{
	DB *database = new DB();
	database->createDB();
	database->setData("url", "user", "coment");
	database->getData();
	string url = database->geturl();
	string user = database->getuser();
	string coment = database->getcoment();
	
	assert(database->geturl() == url);
	assert(database->getuser() == user);
	assert(database->getcoment() == coment);

	Myftp *ftp;
	CListCtrl listView;
	char *Files[NUM];
	char *Leng[NUM];

	ftp = new Myftp(&listView, _T("ftp://192.168.0.104/"), _T("q"), _T("q"), _T("C:\\Users\\mixon\\Desktop\\ftpClient\\"));

	url = CT2CA(ftp->MyGetURL()); 
	string path = CT2CA(ftp->MyGetPath());
	assert("ftp://192.168.0.104" == url);
	assert("/"== path);

	BOOL flag = ftp->MyConnect();
	assert(flag == TRUE);

	int numFiles = ftp->MyPrintFiles(Files, Leng);
	assert(numFiles == 2);
	assert(Leng[0] == "22");

	flag = ftp->onCopy();
	assert(flag == TRUE);

}