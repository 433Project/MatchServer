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
	
	ConsoleLogger::PrintMessage("ClientHolder 초기화");
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
	
	(waitingList + idx)->clientList.push_back(client);

	// client info list에 넣는다.
	clientInfoList.insert({client.GetClientId(), client});
	
	return true;
}

// 아직 미구현

//Client ClientHolder::GetClient(CLIENTID clientId) {
//	//
//	return ;
//}

// waiting list, info list에서 매칭 완료된 client를 제거한다. 
bool ClientHolder::DeleteClient(CLIENTID clientId) {

	Client client = clientInfoList[clientId];

	int idx = sizeof(ROOM) * client.GetClientId();

	//(waitingList + idx)->clientList.insert({ client.GetClientId, client });
	int clientIdx = 0;
	for (auto it = (waitingList + idx)->clientList.begin(); ; ++it) {

		if (it->GetClientId() == clientId) {
			// waiting list clear
			(waitingList + idx)->clientList.erase((waitingList + idx)->clientList.begin()+ clientIdx); // 뭐지 
			
			// client info list clear
			clientInfoList.erase(clientId);
			return true;
		}

		clientIdx++;
	}

	return false;
}

