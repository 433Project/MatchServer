#pragma once
#include "common.h"

class Client
{
public:
	Client();
	Client(int clientId, int metric, int serverId, int state, bool attacthed);
	~Client();
	
	bool SetMetric(int);
	int GetMetric();
	int GetServerId();
	//int GetState();
	
	CLIENTID GetClientId();

private: 
	CLIENTID clientId;
	int metric;
	int serverId;
	int state;
	bool attacthed;// 내 서버인지 남의 서버인지 // 필요한가?

};

