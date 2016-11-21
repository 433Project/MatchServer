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
	//Connection Server
	char* csIP = "10.100.10.8";
	
	Logger& log = Logger::GetInstance();
	
};

