#pragma once
#include "Matcher.h"
#include "MessageQueue.h"
#include "ClientHolder.h"


Matcher* Matcher::instance = nullptr;

MessageQueue* messageQueue;

Matcher::Matcher() {
	messageQueue = MessageQueue::GetInstance();
	commandHandler = new CommandHandler();
	clientHolder = ClientHolder::GetInstance();

}

Matcher::~Matcher() {

}

Matcher* Matcher::GetInstance() {
	if (!instance) {
		instance = new Matcher();
	}
	return instance;
}

void Matcher::MainLogic() {

	while (true) {
		Matching();
		HandleMessage();
	}
}

// 그냥 waitingroomlist에서 맞는 짝을 찾기만 하면됨.
void Matcher::Matching() {

	unordered_map<CLIENTID, Client>* connectedClientList = clientHolder->GetConnectedClientList();
	int opposite;

	for (auto it = connectedClientList->cbegin(); it != connectedClientList->cend(); ++it) {
		
		opposite = FindOpposite(it->second);
		
		// send matching result to Room Manager
		if (opposite != -1) {
			// send to room manager
			// cmd: create room request
		}
	}// end loop
}

// MessageQueue에 있는 message를 읽어서 처리한다.
void Matcher::HandleMessage() {
	
	Message msg;

	while (!messageQueue->IsEmpty()) {
		msg = messageQueue->Pop();

		commandHandler->HandleCommand(msg);
	}
}


int Matcher::FindOpposite(Client client) {

	WaitingRoomList waitingList = clientHolder->GetWaitingRoomList();
	int moveUnit = sizeof(ROOM);
	int currentClientMetric = client.GetMetric();
	int move = 0;
	Client opposite;

	while (currentClientMetric + move <= MAX_METRIC || currentClientMetric - move >= MIN_METRIC) {

		// move right
		if (currentClientMetric + move <= MAX_METRIC) {
			// metric과 가까운 대기 client가 존재한다.
			if ((waitingList + (currentClientMetric + move)*moveUnit)->clientList.size() != 0) {

				// latency check
				// get oppoisite client
				// opposite = (waitingList + move)->clientList.begin()->second;
				// opposite = (waitingList + move)->clientList.front();

				for (auto it = (waitingList + move)->clientList.begin(); ; ++it) {
					// latency check
				}

				// if latency check : ok 
				return opposite.GetClientId();

				// else : fail
				// continue;
			}
		}

		// move left
		if (currentClientMetric - move >= MIN_METRIC) {
			// metric과 가까운 대기 client가 존재한다.
			if ((waitingList + (currentClientMetric - move)*moveUnit)->clientList.size() != 0) {

				// latency check
				// if latency check : ok 
				return opposite.GetClientId();

				// else : fail
				// continue;
			}
		}
		move++;
	}// end loop

	return 0;
}

int Matcher::FindOpposite(Client client) {

	WaitingRoomList waitingList = clientHolder->GetWaitingRoomList();
	int moveUnit = sizeof(ROOM);
	int currentClientMetric = client.GetMetric();
	int move = 0;
	Client opposite;

	while (currentClientMetric + move <= MAX_METRIC || currentClientMetric - move >= MIN_METRIC) {

		// move right
		if (currentClientMetric + move <= MAX_METRIC) {
			// metric과 가까운 대기 client가 존재한다.
			if ((waitingList + (currentClientMetric + move)*moveUnit )->clientList.size() != 0) {

			
				// latency check
				// get oppoisite client
				//opposite = (waitingList + move)->clientList.begin()->second;
				// opposite = (waitingList + move)->clientList.front();
				 
				for (auto it = (waitingList + move)->clientList.begin(); ; ++it) {

					// latency holder
					// latency check
					it->GetServerId();

					// if latency is ok 
					return it->GetClientId();
				}
			}
		}

		// move left
		if (currentClientMetric - move >= MIN_METRIC) {
			// metric과 가까운 대기 client가 존재한다.
			if ((waitingList + (currentClientMetric - move)*moveUnit)->clientList.size() != 0) {

				// latency check
				// get oppoisite client
				//opposite = (waitingList + move)->clientList.begin()->second;
				// opposite = (waitingList + move)->clientList.front();

				for (auto it = (waitingList + move)->clientList.begin(); ; ++it) {

					// latency holder
					// latency check
					it->GetServerId();

					// if latency is ok 
					return it->GetClientId();
				}
			}
		}
		move++;
	}// end loop

	return -1;
}

























/*
Matcher::Matcher() {
	clientHolder = ClientHolder::GetInstance();
	metricGenerator = new MetricGenerator();
}

Matcher::~Matcher() {
	delete clientHolder;
	delete metricGenerator;
}

// 1) metric 생성
// 2 list에 추가 
// 3) br
// 4) matching 수행 
void Matcher::Matching(Client client) {

	// 1) metric 생성
	int metric = metricGenerator->GenerateMetric();
	client.SetMetric(metric);

	// 2) list에 추가 
	clientHolder->AddClient(metric, client);

	// 3) br

	// 4) matching 수행
	// int oppositeId = FindOpposite(client);

	// 5) 매칭결과 BR 
}


// Room Manager로부터 matching 에 대해 응답을 받으면, delete Client를 수행하고, client에게 돌려준다. 



int Matcher::FindOpposite(Client client) {

	WaitingList waitingList = clientHolder->GetWaitingList();
	int moveUnit = sizeof(ROOM);
	int currentClientMetric = client.GetMetric();
	int move = 0;
	Client opposite;

	while (currentClientMetric + move <= MAX_METRIC || currentClientMetric - move >= MIN_METRIC) {

		// move right
		if (currentClientMetric + move <= MAX_METRIC) {
			// metric과 가까운 대기 client가 존재한다.
			if ((waitingList + (currentClientMetric + move)*moveUnit )->clientList.size() != 0) {

			
				// latency check
				// get oppoisite client
				//opposite = (waitingList + move)->clientList.begin()->second;
				// opposite = (waitingList + move)->clientList.front();
				 

				for (auto it = (waitingList + move)->clientList.begin(); ; ++it) {
					// latency check
				}

				// if latency check : ok 
				return opposite.GetClientId();

				// else : fail
				// continue;
			}
		}

		// move left
		if (currentClientMetric - move >= MIN_METRIC) {
			// metric과 가까운 대기 client가 존재한다.
			if ((waitingList + (currentClientMetric - move)*moveUnit)->clientList.size() != 0) {

				// latency check
				// if latency check : ok 
				return opposite.GetClientId();

				// else : fail
				// continue;
			}
		}
		move++;
	}// end loop

	return 0;
}
*/
