#pragma once
#include <iostream>
#include <winsock2.h>
#include <MSWSock.h>
#include <process.h>

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

struct PER_HANDLE_DATA
{
	SOCKET hClntSock;
	int clntID;

	PER_HANDLE_DATA(SOCKET sock)
	{
		memset(this, 0, sizeof(*this));
		hClntSock = sock;
	}
};
typedef PER_HANDLE_DATA* LPPER_HANDLE_DATA;

struct PER_IO_DATA : OVERLAPPED
{
	char* buffer;
	WSABUF wsaBuf;
};
typedef PER_IO_DATA* LPPER_IO_DATA;

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
	char* confIP = "10.100.10.10";
	int confPort = 14040;
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

	LPPER_IO_DATA PerIoData;			//CompletionKey
	LPPER_HANDLE_DATA PerHandleData;	//Overlapped Struct

	int port = 10000;
};

