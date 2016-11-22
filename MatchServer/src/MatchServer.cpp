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
	logger.Info("Listen Socket");
	if (socket->CreateListenSocket())
	{
		socket->AcceptEX(5);
	}
	else 
	{
		exit(0);
	}
	
	//2. config server
	logger.Info("Config Server");
	socket->CreateSocket(CONFIG, cfIP);
	
	//3. connection server  
	/*logger.Info("Connection Server");
	if (!socket->CreateSocket(CONNECTION, csIP)) 
	{
		exit(0);
	}*/
}
