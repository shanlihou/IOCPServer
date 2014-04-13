#ifndef DISPLAYFUN_H
#define DISPLAYFUN_H

#include "IOCP.h"

#include <vector>
#include "read_only_class.h"
#include "AccessManager.h"

enum EDIT_ID
{
	ID_EDIT_VALUE1 = 1,
	ID_EDIT_VALUE2,
	ID_EDIT_VALUE3,
	ID_EDIT_VALUE4,
	ID_EDIT_VALUE5,
	ID_EDIT_LIST_NAME,
	ID_EDIT_VAL_REC1,
	ID_EDIT_VAL_REC2,
	ID_EDIT_VAL_REC3,
	ID_EDIT_VAL_REC4,
	ID_EDIT_VAL_REC5,
	ID_EDIT_REC,
	ID_EDIT_SEND,
	ID_EDIT_DIR,
	ID_EDIT_FILE_NAME,
	ID_ASSIGN,
	ID_SAVE,
	ID_DELETE,
	ID_SEND,
	ID_RECV_FILE,
	ID_RECV_INQUIRE
};
struct CQuery
{
public:
	TCHAR* valueName;
	TCHAR* subName;
	bool bState;
};
class ObjManager
{
public:
	(static ObjManager*) getInstance();
	~ObjManager();
	void ObjInit(HINSTANCE hInstance, HWND hwnd);
	void EditDisplay ();

	void OnCreate ();

	void OnPaint ();

	void OnCommand (WPARAM wParam, LPARAM lParam);

	static void IOCPThread(PVOID pvoid);

	std::vector<read_only_edit> m_edit;
	HWND m_hwndMain;
private:
	ObjManager();
	static ObjManager* m_instance;

	std::vector<HWND> m_button;
	HINSTANCE m_hInstance;
	HDC m_hdc;
	CDataBase m_CDBSocket;

};


#endif
