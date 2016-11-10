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
	int metric; // �ɷ�ġ
	int serverId; // connected server unique id 
	ClientState state; // 
	
	bool attacthed;// �� �������� ���� �������� // �ʿ��Ѱ�?

};

