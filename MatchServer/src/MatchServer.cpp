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
		return;
	}
}

void MatchServer::Start() 
{
	//1. listen socket
	if (socket->CreateLinstenSocket(port))
	{
		socket->AcceptEX(5);
	}
	else 
	{
		exit(0);
	}
	
	//2. config server
	if (!socket->CreateSocket(CONFIG, cfIP, cfPort)) 
	{
		//log : [warning] fail to connect config server;
		//but continue 
	}
	
	//3. connection server  
	if (!socket->CreateSocket(CONNECTION, csIP, csPort))
	{
		exit(0);
	}
}
