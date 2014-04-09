#ifndef ACCESSMAN_H
#define ACCESSMAN_H
#include <windows.h>
#include <windowsx.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
class CDataBase
{
public:
	SQLHENV henv;
    
	SQLHDBC hdbc;
    
	SQLHSTMT hstmt;

	SQLWCHAR * ListName;

	SQLWCHAR ** ValueName;

	DWORD NumOfValue;

	CDataBase (DWORD Num);
	~CDataBase ();

	void ConstructNOV (SQLWCHAR * szConstr);

	void DataBaseInit (HWND hwnd);

	void DataBaseFree();

	void SaveToDataBase (HWND hwnd, int NumOfValue, TCHAR **ValueName);

	int inquireDB(HWND hwnd, TCHAR *ValName, TCHAR *SubName);

	void DeleteDB (HWND hwnd, TCHAR *ValName, TCHAR *SubName);

	//void Login(HWND hwnd);
};
#endif
