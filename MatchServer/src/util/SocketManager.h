#pragma once
#include "IOCPManager.h"
#include "Logger.h"
#include "AppConfig.h"

class MessageManager;
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
	void CloseSocketMS(int id);
	void HeartBeats();

private:
	PVOID GetSockExtAPI(GUID guidFn);
	
public:
	SOCKET listenSock;	
	SOCKET csSocket;
	SOCKET cfSocket;
	std::unordered_map<int, SOCKET> msList;
	unordered_map<int, int> heartbeats;
	int packetSize = 100;

private:
	const int backlog = 10;
	static SocketManager* instance;
	IOCPManager* iocpM;
	MessageManager* msgM;
	Logger& logger = Logger::GetInstance();
	AppConfig& config = AppConfig::GetInstance();


	int cfPort = 14040;
	int csPort = 8433;
	int port = 10000;
};

