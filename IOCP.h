#ifndef __IOCP_H_
#define __IOCP_H_

//////////////////////////////////////////////////////////////////////////

#include <winsock2.h>
#include <mswsock.h>

#include <windows.h>
#include <iostream>

#include "DataStruct.h"

//////////////////////////////////////////////////////////////////////////

static 	GUID g_GUIDAcceptEx		= WSAID_ACCEPTEX;
static  GUID g_GUIDTransmitFile = WSAID_TRANSMITFILE;

//////////////////////////////////////////////////////////////////////////


class CIOCP
{
public:
	CIOCP();
	virtual ~CIOCP();
public:
	IO_GROUP			m_io_group;
	KEY_GROUP			m_key_group;

	HANDLE              m_h_iocp;
	SOCKET              m_listen_socket;

	LPFN_TRANSMITFILE   lpTransmitFile;
	LPFN_ACCEPTEX       lpAcceptEx;

	UINT                uPort;
	char                szAddress[20];
	
	int					m_n_thread_count;
	HANDLE              m_h_thread[MAXTHREAD_COUNT];
	HANDLE              m_h_accept_event;

public:
	BOOL				Init();
	BOOL				MainLoop();
private:
	void				InitIoContext(IOCP_IO_PTR lp_io);
	void				Close();
	BOOL				RegAcceptEvent();
	void				CheckForInvalidConnection();
	BOOL				DataAction(IOCP_IO_PTR lp_io,IOCP_KEY_PTR lp_key);
	BOOL				HandleData(IOCP_IO_PTR lp_io,int nFlags);
	BOOL				GetFunPointer();
	BOOL				StartThread();
	BOOL				BindAndListenSocket();
	void				CloseThreadHandle( int count );
	BOOL				InitSocket();
	static DWORD WINAPI	CompletionRoutine(LPVOID lp_param);
	BOOL				PostAcceptEx();
	BOOL				GetAddrAndPort(char*buf,char ip[],UINT &port);
};

//////////////////////////////////////////////////////////////////////////

#endif	//__IOCP_H_

