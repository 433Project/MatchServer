#include "ClientHolder.h"
#include "ConsoleLogger.h"

ClientHolder* ClientHolder::instance = nullptr;
ClientHolder::ClientHolder()
{	
	waitingList = (ROOM*) malloc(sizeof(ROOM) * MAX_METRIC);
	memset(waitingList, 0, sizeof(ROOM) * MAX_METRIC);
	
	ConsoleLogger::PrintMessage("ClientHolder 초기화");
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
// 대기열 포인터 반환
WaitingList ClientHolder::GetWaitingList() {
	return this->waitingList;
}

// =========================================
// ===================Business Logic
// =========================================

// 매칭 요청한 client를 대기열에 넣는다.
bool ClientHolder::AddClient(int metric, Client client) {
	
	// 대기열에 넣는다.
	int idx = sizeof(ROOM) * metric;

	//(waitingList + idx)->clientList.insert({client.GetClientId, client});

	(waitingList + idx)->clientList.push_back(client.GetClientId);
	(waitingList + idx)->count++;


	// client info list에 넣는다.
	clientInfoList.insert({client.GetClientId, client});

	return true;
}

Client ClientHolder::GetClient(CLIENTID clientId) {
	//
}

// 매칭 대기열에서 client를 제거한다. 
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
