#include "AccessManager.h"

#define LOGIN_TIMEOUT 30
#define MAXBUFLEN 255

#define CHECKDBSTMTERROR (hwnd, result, hstmt) if (SQL_ERROR == result){ShowDBStmtError (hwnd, hstmt);return;}

CDataBase::CDataBase (DWORD Num)
{
	henv = NULL;
	hdbc = NULL;
	hstmt = NULL;
	NumOfValue = Num;
	ListName = (SQLWCHAR *) malloc (sizeof (SQLWCHAR) * 20);
	ValueName = (SQLWCHAR **) malloc (sizeof (SQLWCHAR *) * Num);
	for (int i = 0; i < Num; i ++)
	{
		*(ValueName + i) = (SQLWCHAR *) malloc (sizeof (SQLWCHAR) * 20);
	}
}
void ShowDBError (HWND hwnd, SQLSMALLINT type, SQLHANDLE sqlHandle)
{
    TCHAR pStatus[10], pMsg[101];
    SQLSMALLINT SQLmsglen;
    TCHAR error[200] = {0};
    SQLINTEGER SQLerr;
    long erg2 = SQLGetDiagRec (type, sqlHandle, 1,

		(SQLWCHAR *) pStatus, &SQLerr, (SQLWCHAR *) pMsg, 100, &SQLmsglen);

    wsprintf (error, TEXT ("%s (%d)\n"), pMsg, (int) SQLerr);

    MessageBox (hwnd, error, TEXT ("数据库执行错误"), MB_ICONERROR | MB_OK);
}

void ShowDBConnError (HWND hwnd, SQLHDBC hdbc)
{
	ShowDBError (hwnd, SQL_HANDLE_DBC, hdbc);
}

void ShowDBStmtError (HWND hwnd, SQLHSTMT hstmt)
{
	ShowDBError (hwnd, SQL_HANDLE_STMT, hstmt);
}

void CDataBase::DataBaseInit (HWND hwnd)
{
    SQLRETURN result;
    //SQLCHAR ConnStrIn[MAXBUFLEN] = "DRIVER={MySQL ODBC 5.1 Driver};SERVER=127.0.0.1;UID=root;PWD=root;DATABASE=test1;CharSet=gbk;";
    SQLWCHAR ConnStrIn[MAXBUFLEN] = TEXT("Driver={Microsoft Access Driver (*.mdb)};Dbq=c:\\mydatabase.mdb;Uid=Admin;Pwd=;CharSet=gbk;");

	SQLWCHAR ConnStrOut[MAXBUFLEN];

//分配环境句柄
    result = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

//设置管理环境属性
    result = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
//分配连接句柄
    result = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
//设置连接属性
    result = SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (void*)LOGIN_TIMEOUT, 0);
//连接数据库
    result = SQLDriverConnect (hdbc, NULL,

                              ConnStrIn, SQL_NTS,

                              ConnStrOut, MAXBUFLEN,

                              (SQLSMALLINT *)0, SQL_DRIVER_NOPROMPT);

    if(SQL_ERROR==result)
    {
   	   ShowDBConnError(hwnd,hdbc);
   	   return;
    }
//初始化语句句柄
    result = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    //SQL_NTS telling the function the previous parameter is Null-Terminated String, 
	//please alculate the string length for me   
}
void CDataBase::DataBaseFree()
{
	SQLFreeStmt (hstmt, SQL_CLOSE);

    SQLDisconnect (hdbc);

    SQLFreeHandle (SQL_HANDLE_DBC, hdbc);

    SQLFreeHandle (SQL_HANDLE_ENV, henv);
}
void CDataBase::ConstructNOV (SQLWCHAR * szConstr)
{
	wsprintf (szConstr, TEXT("insert into %s("),ListName);

	for (int i = 0; i < NumOfValue; i ++)
	{
		if (i == 0)
		{
			wcscat (szConstr, *(ValueName + i));
		}
		else
		{
			wcscat (szConstr, TEXT (","));
			wcscat (szConstr, *(ValueName + i));
		}
	}
	wcscat (szConstr, TEXT(") values("));
}
void CDataBase::DeleteDB (HWND hwnd, TCHAR *ValName, TCHAR *SubName)
{
	SQLWCHAR sql[255];
	DWORD result;

	wsprintf (sql, TEXT ("delete from %s where "), ListName);

	wcscat (sql, ValName);

	wcscat (sql, TEXT("='"));

	wcscat (sql, SubName);

	wcscat (sql, TEXT("'"));

    result = SQLPrepare (hstmt, (SQLWCHAR*) sql, SQL_NTS);

    if (SQL_ERROR == result){ShowDBStmtError (hwnd, hstmt);return;}

    result = SQLExecute (hstmt);

    if (SQL_ERROR == result){ShowDBStmtError (hwnd, hstmt);return;}
}
void CDataBase::SaveToDataBase (HWND hwnd, int NumOfValue, TCHAR **ValueName)
{
	SQLRETURN result;
	TCHAR szTemp[255];
	TCHAR sql[255];

	ConstructNOV (szTemp);

	for (int i = 0; i < NumOfValue; i ++)
	{
		if (i != NumOfValue - 1)
			wcscat (szTemp, TEXT("'%s',"));
		else
			wcscat (szTemp, TEXT("'%s'"));
		wsprintf(sql, szTemp, *(ValueName + i));

		wsprintf(szTemp, sql);

	}
	wcscat (sql, TEXT(")"));
//	wsprintf(sql, TEXT("insert into T_User(FUserName,FPassword) values('%s','%s')"), userName, password);	

	result = SQLPrepare (hstmt, (SQLWCHAR*) sql, SQL_NTS);

	if (SQL_ERROR == result){ShowDBStmtError (hwnd, hstmt);return;}
    
	result = SQLExecute (hstmt);

	if (SQL_ERROR == result){ShowDBStmtError (hwnd, hstmt);return;}
}
/*
void CDataBase::Login(HWND hwnd)
{
	SQLRETURN result;
	TCHAR sql[255];
	ZeroMemory(sql,sizeof(sql)/sizeof(TCHAR));
	
	wsprintf (sql, TEXT ("select FPassword from T_User where FUserName='%s'"), inputUserName);

	result = SQLPrepare (hstmt, (SQLWCHAR*) sql, SQL_NTS);

	if (SQL_ERROR == result){ShowDBStmtError (hwnd, hstmt);return;}

    result = SQLExecute (hstmt);

    if (SQL_ERROR == result){ShowDBStmtError (hwnd, hstmt);return;}

	SQLINTEGER cbsatid = SQL_NTS;

	BOOL found = FALSE;

	while (SQLFetch (hstmt) != SQL_NO_DATA_FOUND)
    {
		TCHAR password[20];
		SQLGetData(hstmt,1,SQL_C_CHAR,password,sizeof(password)/sizeof(TCHAR),&cbsatid);
    }
}
*/