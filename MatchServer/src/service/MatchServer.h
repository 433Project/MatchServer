#pragma once

#include "MessageManager.h"
#include "SocketManager.h"
using namespace std;

enum CompletionKey :int
{
	KEY_CONFIG_SERVER,
	KEY_CONNECTION_SERVER,
	KEY_MATCH_SERVER,
	KEY_LISTEN_SOCKET
};

class MatchServer
{
public:
	MatchServer();
	~MatchServer();
	void RunServer();

private:
	static HANDLE CreateNewCompletionPort(DWORD dwNumberOfConcurrentThreads);
	static BOOL AssociateDeviceWithCompletionPort(HANDLE hCompletionPort, HANDLE hDevice, DWORD dwCompletionKey);
	static unsigned int __stdcall ProcessThread(LPVOID hCompletion);

private:
	int packetSize;
	int headerSize;

	WSADATA wsd;
	//Config Server 
	char* confIP = "10.100.10.10";
	int confPort = 14040;
	SOCKET hConfigSock;
	SOCKADDR_IN configAddr;

	//Connection Server
	char* connIP = "10.100.10.6";
	int connPort = 8433;
	SOCKET hConnSock;
	SOCKADDR_IN connAddr;

	SOCKET hsoListen;
	int backlog = 10;
	static const int port = 10000;

	SYSTEM_INFO si;
	HANDLE hCompletion;
		
	
};

