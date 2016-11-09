#pragma once
#include <iostream>
#include <winsock2.h>
#include <MSWSock.h>
#include <process.h>

#include "MessageManager.h"

#pragma comment(lib, "Ws2_32.lib")
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
	SOCKET GetConnectSocket(char* ip, int port);
	static HANDLE CreateNewCompletionPort(DWORD dwNumberOfConcurrentThreads);
	static BOOL AssociateDeviceWithCompletionPort(HANDLE hCompletionPort, HANDLE hDevice, DWORD dwCompletionKey);

	PVOID GetSockExtAPI(SOCKET sock, GUID guidFn);
	void AcceptEX(SOCKET hsoListen, int count);
	SOCKET GetListenSocket(short shPortNo, int nBacklog);

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
	int connPort = 10433;
	SOCKET hConnSock;
	SOCKADDR_IN connAddr;

	SOCKET hsoListen;
	int backlog = 10;

	SYSTEM_INFO si;
	HANDLE hCompletion;

	LPPER_IO_DATA PerIoData;		
	//LPPER_HANDLE_DATA PerHandleData;

	int port = 10000;
};

