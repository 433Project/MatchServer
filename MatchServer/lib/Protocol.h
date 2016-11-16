#pragma once
#include <string>
#include "Packet_generated.h"
using namespace std;
using namespace fb;

enum TERMINALTYPE :int
{
	MATCHING_SERVER = 0,
	MATCHING_CLIENT,
	ROOM_SERVER,
	PACKET_GENERATOR,
	MONITORING_SERVER,
	CONFIG_SERVER,
	CONNECTION_SERVER
};

struct Header
{
	int length;
	TERMINALTYPE srcType;
	int srcCode;
	TERMINALTYPE dstType;
	int dstCode;
	Header() {};
	Header(int len, TERMINALTYPE srcType, int srcCode, TERMINALTYPE dstType, int dstCode)
	{
		this->length = len;
		this->srcType = srcType;
		this->srcCode = srcCode;
		this->dstType = dstType;
		this->dstCode = dstCode;
	}
};

struct Packet {
	Header header;
	Body* body;

	Packet(Header header, Body* body) {
		this->header = header;
		this->body = body;
	}
};

struct UserInfo
{
	int	ID;
	int	metric;
};

enum ClientState : int {
	Waiting,
	Reserved
};


struct Policy {

public: 
	static const int MATCHING_INTERVAL = 500; // 500ms
	static const int MATCHING_ATTEMPT = 3; // 3È¸ ½Ãµµ 
	static const int LATENCY_MIN = 0;
	static const int LATENCY_MAX = 1;

};

