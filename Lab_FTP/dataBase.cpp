#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include "database.h"

void DB::setData(string _url, string _user, string _coment)
{
	url = _url;
	user = _user;
	coment = _coment;

	std::string sSQL;
	sSQL.append("INSERT INTO coments VALUES ('");
	sSQL.append(url);
	sSQL.append("', '");
	sSQL.append(user);
	sSQL.append("', '");
	sSQL.append(coment);
	sSQL.append("')");

	PGresult *res = PQexec(conn, sSQL.c_str());
	PQclear(res);
	res = PQexec(conn, "BEGIN");


	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		printf("BEGIN command failed");
		PQclear(res);
		PQfinish(conn);
		exit(1);
	}


	PQclear(res);

	res = PQexec(conn, "DECLARE emprec CURSOR FOR select * from coments");
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		printf("DECLARE CURSOR failed");
		PQclear(res);
		PQfinish(conn);
		exit(1);
	}


	PQclear(res);

	res = PQexec(conn, "FETCH ALL in emprec");

	for (int j = 0; j < PQnfields(res); j++)
	{
		printf("%-30s", PQgetvalue(res, PQntuples(res) - 1, j));
	}
	printf("\n");
	PQclear(res);

	res = PQexec(conn, "CLOSE emprec");
	PQclear(res);

	res = PQexec(conn, "END");

	PQclear(res);
}

void DB::getData()
{
	PGresult *res = PQexec(conn, "BEGIN");


	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		printf("BEGIN command failed");
		PQclear(res);
		PQfinish(conn);
		exit(1);
	}


	PQclear(res);

	res = PQexec(conn, "DECLARE emprec CURSOR FOR select * from ellCoords");
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		printf("DECLARE CURSOR failed");
		PQclear(res);
		PQfinish(conn);
		exit(1);
	}


	PQclear(res);

	res = PQexec(conn, "FETCH ALL in emprec");
	url = PQgetvalue(res, PQntuples(res) - 1, 0);
	user = PQgetvalue(res, PQntuples(res) - 1, 1);
	coment =PQgetvalue(res, PQntuples(res) - 1, 2);

	

	PQclear(res);

	res = PQexec(conn, "CLOSE emprec");
	PQclear(res);

	res = PQexec(conn, "END");

	PQclear(res);
}