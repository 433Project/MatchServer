#include "Matcher.h"
#include "ConsoleLogger.h"

Matcher* Matcher::instance = nullptr;
Matcher* Matcher::GetInstance() {
	if (!instance) {
		instance = new Matcher();
	}
	return instance;
}

Matcher::Matcher() {
	clientHolder = ClientHolder::GetInstance();
	metricGenerator = new MetricGenerator();
	messageQueue = MessageQueue::GetInstance();
}

Matcher::~Matcher() {
	delete clientHolder;
	delete metricGenerator;
}

void Matcher::Process() {

	while (true) {
		Matching();
		HandleMessageQueue();
	}
}

// metric, latency 계산을 통한 상대편 찾기.
void Matcher::Matching() {
	
	unordered_map<CLIENTID, Client>* clientList;
	int oppositeId;

	clientList = clientHolder->GetClientInfoList();
	for (auto client = clientList->begin(); client != clientList->end(); ++client) {

		if (client->second.GetCntTry() >= Policy::MATCHING_ATTEMPT) {
			// exceed attempt limit.
			// matching fail 
			
			// handle matching fail 
		}
		else {
			oppositeId = FindOpposite(client->second);
			if (oppositeId != -1) {
				// found success

				// send message result to RM 
			}
			else {
				// found fail : no opposite
				
			}
			// inc matching attempts
			client->second.IncCntTry();
		}		
	}// end loop 
}

// MessageQueue에 쌓여있는 Message Handle
void Matcher::HandleMessageQueue() {

	Packet packet;
	while (!messageQueue->IsEmpty()) {
		packet = messageQueue->Pop();

		// pass packet to packet handler 
	}
}

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
			if ((waitingList + (currentClientMetric + move)*moveUnit)->clientList.size() != 0) {

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

	return -1;
}

/*
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
	int oppositeId = FindOpposite(client);

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
