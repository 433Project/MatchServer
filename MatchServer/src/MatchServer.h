#pragma once

#include "SocketManager.h"
#include "Logger.h"

using namespace std;


class MatchServer
{
public:
	MatchServer();
	~MatchServer();
	void Initailize();
	void Start();

private:
	IOCPManager* iocp = IOCPManager::GetInstance();
	SocketManager* socket;
	//Config Server 
	char* cfIP = "10.100.10.10";
	int cfPort = 14040;

	//Connection Server
	char* csIP = "10.100.10.8";
	int csPort = 8433;

	SOCKET listen;
	int backlog = 10;
	const int port = 10000;
	Logger& log = Logger::GetInstance();
	
};

