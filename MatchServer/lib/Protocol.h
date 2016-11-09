#pragma once
#include <string>

using namespace std;

enum SrcDstType :int
{
	MATCHING_SERVER = 0,
	MATCHING_CLIENT,
	ROOM_MANAGER,
	PACKET_GENERATOR,
	MONITORING_SERVER,
	CONFIG_SERVER,
	CONNECTION_SERVER
};

struct Header
{
	int length;
	SrcDstType srcType;
	int srcCode;
	SrcDstType dstType;
	int dstCode;
	Header() {};
	Header(int len, SrcDstType srcType, int srcCode, SrcDstType dstType, int dstCode)
	{
		this->length = len;
		this->srcType = srcType;
		this->srcCode = srcCode;
		this->dstType = dstType;
		this->dstCode = dstCode;
	}
};

struct Body {

	Command command;
	string data;
};

struct Packet {
	Header header;
	Body body;
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
};

