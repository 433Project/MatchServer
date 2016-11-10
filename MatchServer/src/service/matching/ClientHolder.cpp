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
	// metric의 크기만큼의 배열을 미리 할당 & set 0
	waitingRoomList = (ROOM*) malloc(sizeof(ROOM) * MAX_METRIC);
	memset(waitingRoomList, 0, sizeof(ROOM) * MAX_METRIC);
	
	ConsoleLogger::PrintMessage("ClientHolder 초기화");
}

ClientHolder::~ClientHolder()
{
	delete waitingRoomList;
	delete instance;
}

//return  waitingroomlist 
WaitingRoomList ClientHolder::GetWaitingRoomList() {
	return this->waitingRoomList;
}

// return connected client list 
unordered_map<CLIENTID, Client>* ClientHolder::GetConnectedClientList() {
	return &(this->connectedClientList);
}

// =========================================
// ===================Business Logic
// =========================================

// 매칭 요청한 client를 대기열에 넣는다.
bool ClientHolder::AddClient(int metric, Client client) {
	
	// 대기열에 넣는다.
	int idx = sizeof(ROOM) * metric;
	(waitingRoomList + idx)->clientList.push_back(client);

	// client info list에 넣는다.
	connectedClientList.insert({client.GetClientId(), client});
	
	return true;
}

// waiting list, info list에서 매칭 완료된 client를 제거한다. 
bool ClientHolder::DeleteClient(CLIENTID clientId) {

	Client client = connectedClientList[clientId];

	int idx = sizeof(ROOM) * client.GetClientId();

	//(waitingRoomList + idx)->clientList.insert({ client.GetClientId, client });
	int clientIdx = 0;
	for (auto it = (waitingRoomList + idx)->clientList.begin(); ; ++it) {

		if (it->GetClientId() == clientId) {
			// waiting list clear
			(waitingRoomList + idx)->clientList.erase((waitingRoomList + idx)->clientList.begin() + clientIdx); // 뭐지 

			// client info list clear
			connectedClientList.erase(clientId);
			return true;
		}

		clientIdx++;
	}
	return false;
}

