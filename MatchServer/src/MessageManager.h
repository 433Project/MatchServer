#pragma once
#include <iostream>
#include <winsock2.h>
#include <MSWSock.h>
#include "Protocol.h"
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

class MessageManager
{
public:
	MessageManager();
	~MessageManager();
	void MessageManager::SendPacket(SOCKET socket, char* buf);
	//void ReceivePacket(SOCKET socket, LPPER_IO_DATA ov);
	char* HeaderToCharPtr(Header *h);
};

