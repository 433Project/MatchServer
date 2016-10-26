#pragma once

#include <iostream>
#include "Client.h"
#include "WaitingRoom.h"
#include "common.h"


#include <unordered_map>

using namespace std;


// MS�� ��û�� Client���� ������ �����Ѵ�.
class ClientHolder
{

public:
	ClientHolder();
	~ClientHolder();

	//================ �ʱ�ȭ ���� 
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

