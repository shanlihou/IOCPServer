#ifndef DISPLAYFUN_H
#define DISPLAYFUN_H
#include <Windows.h>
#include "read_only_class.h"
#include "AccessManager.h"
#define ID_EDIT_VALUE1 1
#define ID_EDIT_VALUE2 2
#define ID_EDIT_VALUE3 3
#define ID_EDIT_VALUE4 4
#define ID_EDIT_VALUE5 5
#define ID_EDIT_LIST_NAME 6
#define ID_EDIT_VAL_REC1 7
#define ID_EDIT_VAL_REC2 8
#define ID_EDIT_VAL_REC3 9
#define ID_EDIT_VAL_REC4 10
#define ID_EDIT_VAL_REC5 11
#define ID_EDIT_REC 12
#define ID_EDIT_SEND 13
#define ID_EDIT_DIR 14
#define ID_EDIT_FILE_NAME 15


#define ID_ASSIGN 21
#define ID_SAVE 22
#define ID_DELETE 23
#define ID_SEND 24
#define ID_RECV_FILE 25

void EditDisplay (read_only_edit *CEdit, HWND hwndParent, HINSTANCE hInstance);

void ButtonDisplay (HWND *CButton, HWND hwnd, HINSTANCE hInstance);

void OnCreate (HWND hwnd, WPARAM wParam, LPARAM lParam, HWND *CButton);

void OnPaint (HDC hdc);

void OnCommand (HWND hwnd, WPARAM wParam, LPARAM lParam, CDataBase *CDBsocket, read_only_edit *ValueName, bool *bSend);

#endif