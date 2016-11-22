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
	bool CreateSocket(int type, char* ip, int id = 0);
	bool CreateListenSocket();
	void AcceptEX(int count);
	DWORD SendPacket(SOCKET socket, char* data);
	void ReceivePacket(SOCKET socket, IO_DATA* ioData);

private:
	PVOID GetSockExtAPI(GUID guidFn);
	
public:
	SOCKET listenSock;	
	SOCKET csSocket;
	SOCKET cfSocket;
	map<SOCKET, int> msList;
	int packetSize = 100;


private:
	const int backlog = 10;
	static SocketManager* instance;

	Logger& logger = Logger::GetInstance();
	IOCPManager* iocp;

	int cfPort = 14040;
	int csPort = 8433;
	int port = 10000;
};

