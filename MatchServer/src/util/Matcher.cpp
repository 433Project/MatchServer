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

// 1) metric ����
// 2 list�� �߰� 
//3) br
//4) matching ���� 
void Matcher::Matching(Client client) {

	// 1) metric ����
	int metric = metricGenerator.GenerateMetric();
	client.SetMetric(metric);

	// 2) list�� �߰� 
	clientHolder->AddClient(metric, client);

	// 3) br

	// 4) matching ����
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
			// metric�� ����� ��� client�� �����Ѵ�.
			if ((waitingList + (currentClientMetric + move)*moveUnit )->count != 0) {

				/*
					�����ؾ���.
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
			// metric�� ����� ��� client�� �����Ѵ�.
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