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

// metric, latency ����� ���� ����� ã��.
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

// MessageQueue�� �׿��ִ� Message Handle
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
			// metric�� ����� ��� client�� �����Ѵ�.
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
			// metric�� ����� ��� client�� �����Ѵ�.
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
// 1) metric ����
// 2 list�� �߰� 
// 3) br
// 4) matching ���� 
void Matcher::Matching(Client client) {

	// 1) metric ����
	int metric = metricGenerator->GenerateMetric();
	client.SetMetric(metric);

	// 2) list�� �߰� 
	clientHolder->AddClient(metric, client);

	// 3) br

	// 4) matching ����
	int oppositeId = FindOpposite(client);

	// 5) ��Ī��� BR 
}


// Room Manager�κ��� matching �� ���� ������ ������, delete Client�� �����ϰ�, client���� �����ش�. 
int Matcher::FindOpposite(Client client) {

	WaitingList waitingList = clientHolder->GetWaitingList();
	int moveUnit = sizeof(ROOM);
	int currentClientMetric = client.GetMetric();
	int move = 0;
	Client opposite;

	while (currentClientMetric + move <= MAX_METRIC || currentClientMetric - move >= MIN_METRIC) {

		// move right
		if (currentClientMetric + move <= MAX_METRIC) {
			// metric�� ����� ��� client�� �����Ѵ�.
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
			// metric�� ����� ��� client�� �����Ѵ�.
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
