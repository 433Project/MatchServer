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
		log.ERROR("WSAStartup fail");
		return;
	}
}

void MatchServer::Start() 
{
	//1. listen socket
	log.INFO("Listen Socket");
	if (socket->CreateListenSocket())
	{
		socket->AcceptEX(5);
	}
	else 
	{
		exit(0);
	}
	
	//2. config server
	log.INFO("Config Server");
	socket->CreateSocket(CONFIG, cfIP);
	
	//3. connection server  
	log.INFO("Connection Server");
	if (!socket->CreateSocket(CONNECTION, csIP)) 
	{
		exit(0);
	}
}
