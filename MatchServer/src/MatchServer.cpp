#include "MatchServer.h"

MatchServer::MatchServer()
{
	iocp = IOCPManager::GetInstance();
	socket = SocketManager::GetInstance();

}

MatchServer::~MatchServer()
{
	WSACleanup();
}

void MatchServer::Initailize() 
{
	WSADATA wsd;
	int nErrCode = WSAStartup(MAKEWORD(2, 2), &wsd);
	if (nErrCode)
	{
		logger.Error("WSAStartup fail : ", nErrCode);
		return;
	}
}

void MatchServer::Start() 
{
	//1. listen socket
	if (socket->CreateListenSocket())
	{
		socket->AcceptEX(5);
	}
	else 
	{
		exit(0);
	}
	
	//2. config server
	if (config.Contains("Config"))
	{
		json cf = config.GetConfig<json>("Config");
		if (!socket->CreateSocket(CONFIG, cf["ip"], cf["port"]))
			logger.Error("Fail to connect Config server. check Config Server's ip, port at app.json");
	}
	else 
	{
		logger.Error("Config Server doesn't exist in app.json");
	}

	//3. connection server  
	if (config.Contains("Connection")) 
	{
		json cs = config.GetConfig<json>("Connection");
		if (!socket->CreateSocket(CONNECTION, cs["ip"], cs["port"]))
			exit(0);
	}
	else
	{
		logger.Error("Connection Server doesn't exist in app.json");
		exit(0);
	}
}
