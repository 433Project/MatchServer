#pragma once
#include <iostream>
#include <winsock2.h>
#include <MSWSock.h>
#include "Protocol.h"
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

class MessageManager
{
public:
	MessageManager();
	~MessageManager();
	void MessageManager::SendPacket(SOCKET socket, char* buf);
	void ReceivePacket(LPPER_HANDLE_DATA PerHandleData);
	char* HeaderToCharPtr(Header *h);
};

