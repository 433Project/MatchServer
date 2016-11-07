#pragma once
#include <iostream>
#include <winsock2.h>
#include <MSWSock.h>
#include "Packet_generated.h"

//#include "Protocol.h"
#pragma comment(lib, "Ws2_32.lib")
using namespace std;
using namespace fb;

struct PER_HANDLE_DATA
{
	//SOCKET hClntSock;
	int clntID;

	/*PER_HANDLE_DATA(SOCKET sock)
	{
		memset(this, 0, sizeof(*this));
		hClntSock = sock;
	}*/
};
typedef PER_HANDLE_DATA* LPPER_HANDLE_DATA;

struct PER_IO_DATA : OVERLAPPED
{
	char buffer[512];
	WSABUF wsaBuf;
	SOCKET hClntSock;

	PER_IO_DATA(SOCKET sock)
	{
		memset(this, 0, sizeof(*this));
		hClntSock = sock;
	}
};
typedef PER_IO_DATA* LPPER_IO_DATA;

class MessageManager
{
public:
	MessageManager();
	~MessageManager();
	void MessageManager::SendPacket(SOCKET socket, char* buf, int len);
	void ReceivePacket(LPPER_IO_DATA PerIoData);
	void ReceiveFlatBuffers(SOCKET s);
	//char* HeaderToCharPtr(Header *h);
	//char* BodyToCharPtr(Command command, char* data);
	//Header* CharPtrToHeader(char* bytes);

public:
	int HEAD_SIZE = 20;
};

