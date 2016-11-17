#pragma once
#include <iostream>
#include <winsock2.h>
#include <MSWSock.h>
#include "Protocol.h"


#pragma comment(lib, "Ws2_32.lib")
using namespace std;

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
	void MakePacket(char* bytes, TERMINALTYPE dstType, int dstCode, COMMAND comm, STATUS st, string data1, string data2);
	void ReadPacket(Packet* p, char* data);


};

