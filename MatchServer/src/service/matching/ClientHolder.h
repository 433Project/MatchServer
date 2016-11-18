#pragma once
#include "Client.h"
#include "WaitingRoom.h"
#include <unordered_map>
#include "Logger.h"

// MS에 요청한 Client들의 정보를 관리한다.
class ClientHolder
{

public:

	~ClientHolder();

	//================ 초기화 관련 
	static ClientHolder& GetInstance();

	WaitingList GetWaitingList();
	unordered_map<CLIENTID, Client> GetClientInfoList();

	// =============== Business Logic 
	bool AddClient(int metric, Client client);

	
	bool DeleteClient(CLIENTID userId);
	//Client GetClient(CLIENTID userId);
	//bool SetClientState(Client client, int state);	
	
	Client ClientHolder::operator[](int a);

private: 
	WaitingList waitingList;
	
	unordered_map<CLIENTID, Client> clientInfoList;  // 현재 MS에 접속해 있는 CLIENT 리스트.
	ClientHolder();
};

