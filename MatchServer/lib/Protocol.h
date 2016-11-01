#pragma once
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

enum Command
{
	MATCH_REQUEST,
	MATCH_COMPLET,
	LATENCY,
	HEALTH_CHECK,
	MSLIST_REQUEST,
	PG_START,
	PG_END
};

struct Header
{
	int length;
	SrcDstType srcType;
	int srcCode;
	SrcDstType dstType;
	int dstCode;

	Header(int len, SrcDstType srcType, int srcCode, SrcDstType dstType, int dstCode)
	{
		this->length = len;
		this->srcType = srcType;
		this->srcCode = srcCode;
		this->dstType = dstType;
		this->dstCode = dstCode;
	}
};

struct UserInfo
{
	int	ID;
	int	metric;
};