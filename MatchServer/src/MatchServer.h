#pragma once
#include "SocketManager.h"
#include "Logger.h"
#include "AppConfig.h"

class MatchServer
{
public:
	MatchServer();
	~MatchServer();
	void Initailize();
	void Start();

private:
	IOCPManager* iocp;
	SocketManager* socket;
	
	//Config Server 
	string cfIP = "10.100.10.10";
	int cfPort = 14040;
	//Connection Server
	string csIP = "10.100.10.8";
	int csPort = 8433;

	Logger& logger = Logger::GetInstance();
	AppConfig& config = AppConfig::GetInstance();
};

