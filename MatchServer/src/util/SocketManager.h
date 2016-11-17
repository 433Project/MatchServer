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
	
	void AcceptEX(int count);
	SOCKET GetListenSocket(short shPortNo, int nBacklog);
	DWORD SendPacket(char* data);
	void ReceivePacket(IO_DATA* ioData);

private:
	PVOID GetSockExtAPI(SOCKET sock, GUID guidFn);

private:
	SOCKET socket;
	int socketType;

public:
	static const int packetSize = 100;

};

