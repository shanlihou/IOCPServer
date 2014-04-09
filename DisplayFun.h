#ifndef DISPLAYFUN_H
#define DISPLAYFUN_H
#include <Windows.h>
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



void EditDisplay (read_only_edit *CEdit, HWND hwndParent, HINSTANCE hInstance);

void ButtonDisplay (HWND *CButton, HWND hwnd, HINSTANCE hInstance);

void OnCreate (HWND hwnd, WPARAM wParam, LPARAM lParam, HWND *CButton);

void OnPaint (HDC hdc);

void OnCommand (HWND hwnd, WPARAM wParam, LPARAM lParam, CDataBase *CDBsocket, read_only_edit *ValueName, bool *bSend);

#endif
