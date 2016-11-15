#pragma once
#include "common.h"
#include "Protocol.h"

class Client
{
public:
	Client();
	Client(int clientId, int metric, int serverId, ClientState state, bool attacthed);
	~Client();
	
	//------- Getter, Setter
	//-- metric
	bool SetMetric(int);
	int GetMetric();
	//-- serverid
	int GetServerId();
	//-- clientid
	CLIENTID GetClientId();
	//-- state
	bool SetState(ClientState state);
	ClientState GetState();
	
	//----cnttry
	int GetCntTry();

	//---- business
	int IncCntTry();

private: 
	CLIENTID clientId;
	int metric;
	int serverId;
	ClientState state;

	int cntTry;
	
	bool attacthed;// 내 서버인지 남의 서버인지 // 필요한가?
};

