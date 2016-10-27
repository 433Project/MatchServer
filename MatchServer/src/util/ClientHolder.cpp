#include "ClientHolder.h"
#include "ConsoleLogger.h"

ClientHolder* ClientHolder::instance = nullptr;
ClientHolder* ClientHolder::GetInstance() {
	ConsoleLogger::PrintMessage("ClientHolder getInstance()");
	if (!instance) {
		instance = new ClientHolder();
	}
	return instance;
}

ClientHolder::ClientHolder()
{	
	waitingList = (ROOM*) malloc(sizeof(ROOM) * MAX_METRIC);
	memset(waitingList, 0, sizeof(ROOM) * MAX_METRIC);
	
	ConsoleLogger::PrintMessage("ClientHolder �ʱ�ȭ");
}

ClientHolder::~ClientHolder()
{

}

// ��⿭ ������ ��ȯ
WaitingList ClientHolder::GetWaitingList() {
	return this->waitingList;
}

// =========================================
// ===================Business Logic
// =========================================

// ��Ī ��û�� client�� ��⿭�� �ִ´�.
bool ClientHolder::AddClient(int metric, Client client) {
	
	// ��⿭�� �ִ´�.
	int idx = sizeof(ROOM) * metric;
	
	(waitingList + idx)->clientList.push_back(client);

	// client info list�� �ִ´�.
	clientInfoList.insert({client.GetClientId(), client});
	
	return true;
}

// ���� �̱���

//Client ClientHolder::GetClient(CLIENTID clientId) {
//	//
//	return ;
//}

// waiting list, info list���� ��Ī �Ϸ�� client�� �����Ѵ�. 
bool ClientHolder::DeleteClient(CLIENTID clientId) {

	Client client = clientInfoList[clientId];

	int idx = sizeof(ROOM) * client.GetClientId();

	//(waitingList + idx)->clientList.insert({ client.GetClientId, client });
	int clientIdx = 0;
	for (auto it = (waitingList + idx)->clientList.begin(); ; ++it) {

		if (it->GetClientId() == clientId) {
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

