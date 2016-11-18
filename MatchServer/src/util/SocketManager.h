#pragma once

#include <iostream>
#include "IOCPManager.h"
#include "MessageManager.h"

using namespace std;

class SocketManager
{
protected:
	SocketManager();
	~SocketManager();

public:
	static SocketManager* GetInstance();
	bool CreateSocket(int type, char* ip, int port);
	bool CreateLinstenSocket(int port);
	void AcceptEX(int count);
	DWORD SendPacket(SOCKET socket, char* data);
	void ReceivePacket(SOCKET socket, IO_DATA* ioData);

private:
	PVOID GetSockExtAPI(GUID guidFn);
	
private:
	SOCKET listenSock;
	const int backlog = 10;
	SOCKET csSocket;
	SOCKET cfSocket;
	set<SOCKET> msList;


	static SocketManager* instance;
	IOCPManager* iocp;
	int packetSize = 100;
};

