#pragma once
#include <iostream>
#include <winsock2.h>
#include <MSWSock.h>
#include <process.h>

#include "MessageManager.h"

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

class MatchServer
{
public:
	MatchServer();
	~MatchServer();
	void RunServer();

private:
	SOCKET GetConnectSocket(char* ip, int port);
	HANDLE CreateNewCompletionPort(DWORD dwNumberOfConcurrentThreads);
	BOOL AssociateDeviceWithCompletionPort(HANDLE hCompletionPort, HANDLE hDevice, DWORD dwCompletionKey);

	PVOID GetSockExtAPI(SOCKET sock, GUID guidFn);
	void AcceptEX(SOCKET hsoListen, int count);
	SOCKET GetListenSocket(short shPortNo, int nBacklog);

	static unsigned int __stdcall ProcessThread(LPVOID hCompletion);

private:
	WSADATA wsd;

	//Config Server 
	char* confIP = "10.100.10.9";
	int confPort = 12345;
	SOCKET hConfigSock;
	SOCKADDR_IN configAddr;

	//Connection Server
	char* connIP = "10.100.10.10";
	int connPort = 10101;
	SOCKET hConnSock;
	SOCKADDR_IN connAddr;

	SOCKET hsoListen;
	int backlog = 10;

	SYSTEM_INFO si;
	HANDLE hCompletion;

	//LPPER_IO_DATA PerIoData;			//CompletionKey
	LPPER_HANDLE_DATA PerHandleData;	//Overlapped Struct

	int port = 10000;
};

