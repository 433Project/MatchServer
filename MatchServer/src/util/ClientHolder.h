#pragma once

#include <iostream>
#include "Client.h"
#include "WaitingRoom.h"
#include "common.h"


#include <unordered_map>

using namespace std;


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

	Client GetClient(CLIENTID userId);
	bool DeleteClient(CLIENTID userId);

	bool SetClientState(Client client, int state);	
	
private: 
	static ClientHolder* instance;
	WaitingList waitingList;
	
	unordered_map<CLIENTID, Client> clientInfoList; 
	
	
};

