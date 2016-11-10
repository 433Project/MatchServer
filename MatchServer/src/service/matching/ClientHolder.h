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

	//================ 초기화 
	static ClientHolder* GetInstance();

	WaitingRoomList GetWaitingRoomList();
	unordered_map<CLIENTID, Client>* GetConnectedClientList();

	// =============== Business Logic 
	bool AddClient(int metric, Client client);

	bool DeleteClient(CLIENTID userId);

	//Client GetClient(CLIENTID userId);
	//bool SetClientState(Client client, int state);	
	
private: 
	static ClientHolder* instance;

	WaitingRoomList waitingRoomList;// 매칭 대상 대기열 
	unordered_map<CLIENTID, Client> connectedClientList;  // 자기한테 붙어있는 client정보 별도 관리
};

