#include"read_only_class.h"

void read_only_edit:: fnReplaceContent (TCHAR * szBuf)
{
	SendMessage (hwndEdit, EM_SETSEL, 0, -1);

	SendMessage (hwndEdit, EM_REPLACESEL, 0, (LPARAM)szBuf);
}

void read_only_edit:: fnGetContent(TCHAR *szBuf, int numOfLine)
{
	int nLength;

	*(LPWORD) szBuf = nSizeOfx;

	nLength = SendMessage (hwndEdit, EM_GETLINE, numOfLine, (LPARAM) szBuf);

	szBuf [nLength] = '\0';
}

void read_only_edit:: fnClassInit (HWND hwndParent, DWORD dwStyle, int x, int y, int nWidth, int nHeight, int ID_EDIT, HINSTANCE hInstance)
{
	hwndEdit = CreateWindow (TEXT ("edit"), NULL,
        
        dwStyle,
        
        x, y, nWidth, nHeight, hwndParent, (HMENU) ID_EDIT,
        
        hInstance, NULL) ;

	nSizeOfx = nWidth;

	nSizeOfy = nHeight;

	IDC_EDIT = ID_EDIT;
}
void read_only_edit:: fnAddContent (TCHAR *szBuf)
{
	SendMessage (hwndEdit, EM_SETSEL, -2, -1);

	SendMessage (hwndEdit, EM_REPLACESEL, 0, (LPARAM)szBuf);
}