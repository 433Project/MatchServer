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
			delay�� �ʿ��Ѱ�?
		*/
		HandleMessageQueue();
	}
}

// ��Ī �õ�
void Matcher::Matching() 
{
	
	unordered_map<CLIENTID, Client> clientList;
	int oppositeId;

	// ���� ms�� ������ �ִ� client list
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
			// metric, latency �� ����Ͽ� ����� ã��.

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

				// 1) �̱��� 
				clientList.at(client->first).SetState(ClientState::Reserved);
				//clientHolder.GetWaitingList()->clientList.


				// 2) �̱���
				/*
				==========================================
				=========================== LOGIC
				==========================================
				*/

			}
			else 
			{
				// found fail : no opposite
				// ���� action�� �־�� �ϳ�??
				// ����μ��� ����. 
			}
			// inc matching attempts
			client->second.IncCntTry();
		}		
	}// end loop 
}

// MessageQueue�� �׿��ִ� Message Handle
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
			�̱��� 
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
			// metric�� ����� ��� client�� �����Ѵ�.
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
			// metric�� ����� ��� client�� �����Ѵ�.
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