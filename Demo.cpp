/*------------------------------------------------------------
HELLOWIN.C -- Displays "Hello, Windows 98!" in client area
(c) Charles Petzold, 1998
------------------------------------------------------------*/

#include "DisplayFun.h"
#include"read_only_class.h"
#include "AccessManager.h"
//#include <windows.h>
#include <string>
bool			  bSend = false;

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT ("HelloWin") ;
	MSG          msg ;
	WNDCLASS     wndclass ;

	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc   = WndProc ;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = hInstance ;
	wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.lpszMenuName  = NULL ;
	wndclass.lpszClassName = szAppName ;

	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, TEXT ("This program requires Windows NT!"), 
			szAppName, MB_ICONERROR) ;
		return 0 ;
	}
	ObjManager::getInstance();
	ObjManager::getInstance()->m_hwndMain = CreateWindow (szAppName,                  // window class name
		TEXT ("Server"), // window caption
		WS_OVERLAPPEDWINDOW,        // window style
		CW_USEDEFAULT,              // initial x position
		CW_USEDEFAULT,              // initial y position
		CW_USEDEFAULT,              // initial x size
		CW_USEDEFAULT,              // initial y size
		NULL,                       // parent window handle
		NULL,                       // window menu handle
		hInstance,                  // program instance handle
		NULL) ;                     // creation parameters

	ShowWindow (ObjManager::getInstance()->m_hwndMain, iCmdShow) ;
	UpdateWindow (ObjManager::getInstance()->m_hwndMain) ;
	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg) ;
		DispatchMessage (&msg) ;
	}
	return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_CREATE:
		ObjManager::getInstance()->ObjInit(((LPCREATESTRUCT) lParam)->hInstance, hwnd);
		ObjManager::getInstance()->EditDisplay ();

		ObjManager::getInstance()->OnCreate();
		return 0 ;

	case WM_PAINT:
		ObjManager::getInstance()->OnPaint();
		return 0 ;

	case WM_COMMAND:
		ObjManager::getInstance()->OnCommand (wParam, lParam);
		return 0;

	case WM_DESTROY:
		PostQuitMessage (0) ;
		return 0 ;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}
/*
{
CIOCP iocp;

if( !iocp.Init() )
{
return 0;
}

iocp.MainLoop();

return 0;
}*/

