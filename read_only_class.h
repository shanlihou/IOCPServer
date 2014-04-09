#ifndef _read_only_class
#define _read_only_class

#include<Windows.h>
/****************************************************************/
class read_only_edit
{
public :
	HWND hwndEdit ;

	int nSizeOfx, nSizeOfy, IDC_EDIT;

	void fnClassInit (HWND hwndParent, DWORD dwStyle, int x, int y, int nWidth, int nHeight, int ID_EDIT, HINSTANCE hInstance);

	void fnReplaceContent (TCHAR *szBuf);

	void fnGetContent (TCHAR *szBuf, int numOfLine);

	void fnAddContent (TCHAR *szBuf);
};
/****************************************************************/

#endif