#pragma once
#include <iostream>
#include <winsock2.h>
#include <MSWSock.h>

#pragma comment(lib, "Ws2_32.lib")
using namespace std;


struct Body
{
	Command com;
	byte* data;
};

enum Command 
{
	MATCH_REQUEST,
	MATCH_COMPLET,
	LATENCY,
	HEALTH_CHECK,
	MSLIST_REQUEST
};


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

private:
	void SendMessage(SOCKET socket, LPPER_IO_DATA ov);
	void ReceiveMessage(SOCKET socket, LPPER_IO_DATA ov);
};

