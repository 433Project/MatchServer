#include "Matcher.h"

Matcher* Matcher::instance = nullptr;
Matcher* Matcher::GetInstance() {
	if (!instance) {
		instance = new Matcher();
	}
	return instance;
}

Matcher::Matcher() {
	metricGenerator = new MetricGenerator();
	messageQueue = MessageQueue::GetInstance();
}

Matcher::~Matcher() {
	delete metricGenerator;
}

void Matcher::Process() 
{

	while (true) {
		Matching();
		/*
			delay가 필요한가?
		*/
		HandleMessageQueue();
	}
}

// 매칭 시도
void Matcher::Matching() 
{
	
	unordered_map<CLIENTID, Client> clientList;
	int oppositeId;

	// 현재 ms에 접속해 있는 client list
	clientList = clientHolder.GetClientInfoList();

	for (auto client = clientList.begin(); client != clientList.end(); ++client) 
	{

		if (client->second.GetCntTry() >= Policy::MATCHING_ATTEMPT) 
		{
			// exceed attempt limit.
			// matching fail 
			
			// handle matching fail


			/*
			==========================================
			=========================== LOGIC
			==========================================
				1) delete client from client info list 
				2) delete client from waitinglist
				3) broadcast failed client id 
			*/
		}
		else {
			// metric, latency 를 고려하여 상대편 찾음.

			oppositeId = FindOpposite(client->second);
			if (oppositeId != -1) 
			{
				// found success
				/*
				==========================================
				=========================== LOGIC
				==========================================
					1) change client state to reserved - clientinfolist, waitinglist 
					2) send matching result to room manager				
				*/

				// 1) 미구현 
				clientList.at(client->first).SetState(ClientState::Reserved);
				//clientHolder.GetWaitingList()->clientList.


				// 2) 미구현
				/*
				==========================================
				=========================== LOGIC
				==========================================
				*/

			}
			else 
			{
				// found fail : no opposite
				// 무언가 action이 있어야 하나??
				// 현재로서는 없다. 
			}
			// inc matching attempts
			client->second.IncCntTry();
		}		
	}// end loop 
}

// MessageQueue에 쌓여있는 Message Handle
void Matcher::HandleMessageQueue() 
{

	Packet* packet;
	//Packet packet;
	while (!messageQueue->IsEmpty()) 
	{
		packet = messageQueue->Pop();

		// pass packet to packet handler 
		/*
			=====================================================
			================================= call packet handler
			=====================================================
			미구현 
		*/
	}
}

int Matcher::FindOpposite(Client client) 
{

	WaitingList waitingList = clientHolder.GetWaitingList();
	int moveUnit = sizeof(ROOM);
	int currentClientMetric = client.GetMetric();
	int move = 0;
	Client opposite;

	while (currentClientMetric + move <= MAX_METRIC || currentClientMetric - move >= MIN_METRIC) 
	{

		// move right
		if (currentClientMetric + move <= MAX_METRIC) 
		{
			// metric과 가까운 대기 client가 존재한다.
			if ((waitingList + (currentClientMetric + move)*moveUnit)->clientList.size() != 0) 
			{

				// latency check
				// get oppoisite client
				//opposite = (waitingList + move)->clientList.begin()->second;
				// opposite = (waitingList + move)->clientList.front();

				for (auto it = (waitingList + move)->clientList.begin(); ; ++it) 
				{
					// latency check
				}

				// if latency check : ok 
				// return opposite.GetClientId();

				// else : fail
				// continue;
			}
		}

		// move left
		if (currentClientMetric - move >= MIN_METRIC) 
		{
			// metric과 가까운 대기 client가 존재한다.
			if ((waitingList + (currentClientMetric - move)*moveUnit)->clientList.size() != 0) 
			{

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