#pragma once
#include "common.h"


class MatchingServer
{
public:
	
	//---- 
	MatchingServer();
	~MatchingServer();

	//---- getter setter 
	SERVERID GetServerId();
	int GetLatency();
	
private:
	SERVERID serverId;
	int latency;

};

