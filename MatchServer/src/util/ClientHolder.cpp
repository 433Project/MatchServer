#include "ClientHolder.h"
#include "ConsoleLogger.h"

ClientHolder* ClientHolder::instance = nullptr;
ClientHolder::ClientHolder()
{	
	waitingList = (ROOM*) malloc(sizeof(ROOM) * MAX_METRIC);
	memset(waitingList, 0, sizeof(ROOM) * MAX_METRIC);
	
	ConsoleLogger::PrintMessage("ClientHolder �ʱ�ȭ");
}

ClientHolder* ClientHolder::GetInstance() {
	ConsoleLogger::PrintMessage("ClientHolder getInstance()");
	if (!instance) {
		instance = new ClientHolder();
	}
	return instance;
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

	//(waitingList + idx)->clientList.insert({client.GetClientId, client});

	(waitingList + idx)->clientList.push_back(client.GetClientId);
	(waitingList + idx)->count++;


	// client info list�� �ִ´�.
	clientInfoList.insert({client.GetClientId, client});

	return true;
}

Client ClientHolder::GetClient(CLIENTID clientId) {
	//
}

// ��Ī ��⿭���� client�� �����Ѵ�. 
bool ClientHolder::DeleteClient(CLIENTID clientId) {
	int idx = sizeof(ROOM) * ;

	//(waitingList + idx)->clientList.insert({ client.GetClientId, client });
	(waitingList + idx)->clientList
	(waitingList + idx)->count++;
}

/*****
map<string, Client> ClientHolder::GetClientList() {
	return instance->clientMap;
}
*/
