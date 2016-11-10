#pragma once
#include "common.h"
#include "Protocol.h"

class Client
{
public:
	Client();
	Client(int clientId, int metric, int serverId, bool attacthed);
	Client(int clientId, int metric, int serverId, ClientState state, bool attacthed);
	~Client();
	
	//-- metric
	bool SetMetric(int);
	int GetMetric();
	//-- serverid
	int GetServerId();
	
	CLIENTID GetClientId();
	//-- state
	bool SetState(ClientState state);
	ClientState GetState();
	
private: 
	CLIENTID clientId; // client unique id
	int metric; // 능력치
	int serverId; // connected server unique id 
	ClientState state; // 
	
	bool attacthed;// 내 서버인지 남의 서버인지 // 필요한가?

};

