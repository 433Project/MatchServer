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
	static SocketManager* Instance();
	bool CreateSocket(int type, char* ip, int port);
	bool CreateLinstenSocket(int port);
	void AcceptEX(int count);

private:
	static SocketManager* instance;
	PVOID GetSockExtAPI(GUID guidFn);
	IOCPManager *iocp;

public:
	SOCKET listenSock;
	const int backlog = 10;
	SOCKET csSocket;
	SOCKET cfSocket;
	set<SOCKET> msList;
};

