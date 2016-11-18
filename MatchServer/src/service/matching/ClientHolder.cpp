#include "ClientHolder.h"


//ClientHolder* ClientHolder::instance = nullptr;
ClientHolder& ClientHolder::GetInstance() {

	static ClientHolder instance;

	return instance;
}

ClientHolder::ClientHolder()
{	
	// metric�� ũ�⸸ŭ�� �迭�� �̸� �Ҵ� & set 0
	waitingList = (ROOM*) malloc(sizeof(ROOM) * MAX_METRIC);
	memset(waitingList, 0, sizeof(ROOM) * MAX_METRIC);
}

ClientHolder::~ClientHolder()
{
	if (waitingList != nullptr) 
	{
		delete waitingList;
	}
	
	if (instance != nullptr) 
	{
		delete instance;
	}
}

// ��⿭ ������ ��ȯ
WaitingList ClientHolder::GetWaitingList() 
{
	return this->waitingList;
}

unordered_map<CLIENTID, Client> ClientHolder::GetClientInfoList() 
{
	return (this->clientInfoList);
}

// =========================================
// ===================Business Logic
// =========================================

// ��Ī ��û�� client�� ��⿭�� �ִ´�.
bool ClientHolder::AddClient(int metric, Client client) 
{
	
	// ��⿭�� �ִ´�.
	int idx = sizeof(ROOM) * metric;
	(waitingList + idx)->clientList.push_back(client);

	// client info list�� �ִ´�.
	clientInfoList.insert({client.GetClientId(), client});
	
	return true;
}


//Client ClientHolder::operator [](int a) {
//	if(waitinglist)
//}
//

// ���� �̱���
//Client ClientHolder::GetClient(CLIENTID clientId) {
//	//
//	return ;
//}

// waiting list, info list���� ��Ī �Ϸ�� client�� �����Ѵ�. 
bool ClientHolder::DeleteClient(CLIENTID clientId) 
{

	Client client = clientInfoList[clientId];

	int idx = sizeof(ROOM) * client.GetClientId();

	//(waitingList + idx)->clientList.insert({ client.GetClientId, client });
	int clientIdx = 0;
	for (auto it = (waitingList + idx)->clientList.begin(); ; ++it) 
	{

		if (it->GetClientId() == clientId) 
		{
			// waiting list clear
			(waitingList + idx)->clientList.erase((waitingList + idx)->clientList.begin()+ clientIdx); // ���� 
			
			// client info list clear
			clientInfoList.erase(clientId);
			return true;
		}

		clientIdx++;
	}

	return false;
}

