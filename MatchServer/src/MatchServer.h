#pragma once

#include "MessageManager.h"
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

private:
	//Config Server 
	char* cfIP = "10.100.10.10";
	int cfPort = 14040;
	SOCKET cfSock;
	SOCKADDR_IN cfAddr;

	//Connection Server
	char* csIP = "10.100.10.6";
	int csPort = 8433;
	SOCKET csSock;
	SOCKADDR_IN csAddr;

	SOCKET listen;
	int backlog = 10;
	const int port = 10000;
	
};

