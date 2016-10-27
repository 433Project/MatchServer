#include "Matcher.h"


Matcher* Matcher::instance = nullptr;
Matcher* Matcher::GetInstance() {
	if (!instance) {
		instance = new Matcher();
	}
	return instance;
}

Matcher::Matcher() {
	clientHolder = ClientHolder::GetInstance();
}

// 1) metric 생성
// 2 list에 추가 
//3) br
//4) matching 수행 
void Matcher::Matching(Client client) {

	// 1) metric 생성
	int metric = metricGenerator.GenerateMetric();
	client.SetMetric(metric);

	// 2) list에 추가 
	clientHolder->AddClient(metric, client);

	// 3) br

	// 4) matching 수행
	FindOpposite(client);
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
			if ((waitingList + (currentClientMetric + move)*moveUnit )->count != 0) {

				/*
					구현해야함.
				*/
				// latency check
				// get oppoisite client
				opposite = (waitingList + move)->clientList.begin()->second;

				// if latency check : ok 
				return opposite.GetClientId;

				// else : fail
				// continue;
			}
		}

		// move left
		if (currentClientMetric - move >= MIN_METRIC) {
			// metric과 가까운 대기 client가 존재한다.
			if ((waitingList + (currentClientMetric - move)*moveUnit)->count != 0) {

				// latency check
				opposite = (waitingList + move)->clientList.begin()->second;


				// if latency check : ok 
				return opposite.GetClientId;

				// else : fail
				// continue;
			}
		}
		move++;
	}

	return 0;
}