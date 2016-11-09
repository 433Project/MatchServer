#pragma once
#include <iostream>
#include <winsock2.h>
#include <MSWSock.h>
#include "Packet_generated.h"
#include "Protocol.h"

#pragma comment(lib, "Ws2_32.lib")
using namespace std;
using namespace fb;

struct PER_IO_DATA : OVERLAPPED
{
	char* buffer;		
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
	DWORD SendPacket(SOCKET s, char* data);
	void ReceivePacket(LPPER_IO_DATA PerIoData);
	char* MakePacket(SrcDstType dstType, int dstCode, Command comm, Status st, string data);
	Header* ReadHeader(char* data);
	const Body* ReadBody(int len, char* data);

public:
	int headSize = 20;
	int packetSize = 100;


};

