#pragma once

#include <iostream>
#include <winsock2.h>
#include <MSWSock.h>
#include <process.h>
#include "MessageManager.h"

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

class SocketManager
{
public:
	SocketManager();
	~SocketManager();
	SOCKET GetConnectSocket(char* type, char* ip, int port);
	PVOID GetSockExtAPI(SOCKET sock, GUID guidFn);
	void AcceptEX(int count);
	SOCKET GetListenSocket(short shPortNo, int nBacklog);

private:
	SOCKET listenSock;

};

