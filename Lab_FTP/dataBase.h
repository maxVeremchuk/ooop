#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

#pragma comment(lib, "C:\\Program Files\\PostgreSQL\\10\\lib\\libpq.lib")
#include "C:\\Program Files\\PostgreSQL\\10\\include\\libpq-fe.h"

class DB
{
private:
	PGconn * conn;
	string url;
	string user;
	string coment;

public:
	DB()
	{
	}
	~DB()
	{
		PQfinish(conn);
	}
	string geturl()
	{
		return url;
	}
	string getuser()
	{
		return user;

	}
	string getcoment()
	{
		return coment;
	}
	void createDB()
	{
		conn = NULL;
		conn = PQconnectdb("user=postgres password=max12398 dbname=ftp hostaddr=127.0.0.1 port=5432");
		if (PQstatus(conn) != CONNECTION_OK)
		{
			printf("Connection to database failed");
			PQfinish(conn);
			exit(1);
		}
		PGresult *res = PQexec(conn, "CREATE TABLE coments (url char(30), user char(30), coment char(30))");
		PQclear(res);
	}
	void setData(string, string, string);
	void getData();
};
