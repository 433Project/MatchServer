#include "MatchServer.h"

MatchServer::MatchServer()
{
	
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
		log.Error("WSAStartup fail");
		return;
	}
}

void MatchServer::Start() 
{
	//1. listen socket
	log.Info("Listen Socket");
	if (socket->CreateListenSocket())
	{
		socket->AcceptEX(5);
	}
	else 
	{
		exit(0);
	}
	
	//2. config server
	log.Info("Config Server");
	socket->CreateSocket(CONFIG, cfIP);
	
	//3. connection server  
	log.Info("Connection Server");
	if (!socket->CreateSocket(CONNECTION, csIP)) 
	{
		exit(0);
	}
}
