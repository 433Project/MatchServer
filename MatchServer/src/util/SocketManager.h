#pragma once
#include "IOCPManager.h"
#include "Logger.h"

class SocketManager
{
protected:
	SocketManager();
	~SocketManager();

public:
	static SocketManager* GetInstance();
	bool CreateSocket(COMPLETIONKEY type, char* ip, int id = 0);
	bool CreateListenSocket();
	void AcceptEX(int count);
	DWORD SendPacket(SOCKET socket, char* data);
	void ReceivePacket(SOCKET socket, IO_DATA* ioData);
	void AcceptMS(SOCKET sock, int id);

private:
	PVOID GetSockExtAPI(GUID guidFn);
	
public:
	SOCKET listenSock;	
	SOCKET csSocket;
	SOCKET cfSocket;
	std::unordered_map<int, SOCKET> msList;
	int packetSize = 100;


private:
	const int backlog = 10;
	static SocketManager* instance;

	Logger& logger = Logger::GetInstance();
	IOCPManager* iocpM;

	int cfPort = 14040;
	int csPort = 8433;
	int port = 10000;
};

