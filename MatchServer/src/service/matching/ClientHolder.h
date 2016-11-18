#pragma once
#include "Client.h"
#include "WaitingRoom.h"
#include <unordered_map>
#include "Logger.h"

// MS�� ��û�� Client���� ������ �����Ѵ�.
class ClientHolder
{

public:

	~ClientHolder();

	//================ �ʱ�ȭ ���� 
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
	
	unordered_map<CLIENTID, Client> clientInfoList;  // ���� MS�� ������ �ִ� CLIENT ����Ʈ.
	ClientHolder();
};

