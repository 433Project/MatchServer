#pragma once
#include "Client.h"
#include "WaitingRoom.h"
#include <unordered_map>

// MS�� ��û�� Client���� ������ �����Ѵ�.
class ClientHolder
{

public:
	ClientHolder();
	~ClientHolder();

	//================ �ʱ�ȭ ���� 
	static ClientHolder* GetInstance();

	WaitingRoomList GetWaitingList();
	
	// =============== Business Logic 
	bool AddClient(int metric, Client client);

	bool DeleteClient(CLIENTID userId);
	//Client GetClient(CLIENTID userId);
	//bool SetClientState(Client client, int state);	
	
private: 
	static ClientHolder* instance;

	WaitingRoomList waitingList;// ��Ī ��� ��⿭ 
	unordered_map<CLIENTID, Client> connectedClientList;  // �ڱ����� �پ��ִ� client���� ���� ����
};

