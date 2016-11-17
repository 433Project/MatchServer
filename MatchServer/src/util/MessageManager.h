#pragma once
#include <iostream>
#include <winsock2.h>
#include <MSWSock.h>
#include "Packet_generated.h"
#include "Protocol.h"


#pragma comment(lib, "Ws2_32.lib")
using namespace std;
using namespace fb;

struct IO_DATA : OVERLAPPED
{
	char* buffer;		
	SOCKET hClntSock;

	IO_DATA(SOCKET sock)

	{
		memset(this, 0, sizeof(*this));
		hClntSock = sock;
	}
};

class MessageManager
{

public:
	MessageManager();
	~MessageManager();
	DWORD SendPacket(SOCKET s, char* data);
	void ReceivePacket(IO_DATA* ioData);
	char* MakePacket(TERMINALTYPE dstType, int dstCode, COMMAND comm, STATUS st, string data1, string data2);
	void ReadPacket(Packet* p, char* data);

public:
	int headSize = 20;
	int packetSize = 100;

};

