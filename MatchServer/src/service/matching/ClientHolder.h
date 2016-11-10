#pragma once
#include "Client.h"
#include "WaitingRoom.h"
#include <unordered_map>

// MS에 요청한 Client들의 정보를 관리한다.
class ClientHolder
{

public:
	ClientHolder();
	~ClientHolder();

	//================ 초기화 관련 
	static ClientHolder* GetInstance();

	WaitingList GetWaitingList();
	// =============== Business Logic 
	bool AddClient(int metric, Client client);

	
	bool DeleteClient(CLIENTID userId);
	//Client GetClient(CLIENTID userId);
	//bool SetClientState(Client client, int state);	
	
private: 
	static ClientHolder* instance;
	WaitingList waitingList;
	
	unordered_map<CLIENTID, Client> clientInfoList; 
	
	
};

