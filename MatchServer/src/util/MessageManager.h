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
	void MakePacket(char* bytes, TERMINALTYPE dstType, int dstCode, COMMAND comm, STATUS st, string data1, string data2, int srcCode = 0);
	void ReadPacket(Packet* p, char* data);
	void HeaderToBytes(char* bytes, TERMINALTYPE dstType, int dstCode, int srcCode);
	void BytesToHeader(char* bytes, Header* h);
	void split(const string& s, char del, vector<string>& v);
};

