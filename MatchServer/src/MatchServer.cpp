#include "MatchServer.h"

MatchServer::MatchServer()
{
}

MatchServer::~MatchServer()
{
	
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
	//2. config server
	//3. ms server conn
	//4. connection server  
}
