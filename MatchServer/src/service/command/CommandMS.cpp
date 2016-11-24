#include "CommandMS.h"
#include "SocketManager.h"
#include "MessageManager.h"
#include "MessageQueue.h"

CommandMS::CommandMS()
{
	msgM = new MessageManager();
	msgQ = MessageQueue::GetInstance();
	socketM = SocketManager::GetInstance();
}

CommandMS::~CommandMS()
{
	if (msgM != nullptr)
		delete msgM;
}

void CommandMS::CommandMSHandler(Packet* p)
{
	if (p->body->cmd() == COMMAND_HEALTH_CHECK_REQUEST)
		Command_HEALTH_CHECK_REQUEST(p);
	else if (p->body->cmd() == COMMAND_HEALTH_CHECK_RESPONSE)
		Command_HEALTH_CHECK_RESPONSE(p);
	else
		msgQ->Push(p);
}


void CommandMS::Command_HEALTH_CHECK_REQUEST(Packet* p)
{
	char* data = new char[100];
	msgM->MakePacket(data, p->header->srcType, p->header->srcCode, COMMAND_HEALTH_CHECK_RESPONSE, STATUS_NONE, "", "", socketM->serverID);
	socketM->SendPacket(socketM->cfSocket, data);
	if (data != nullptr)
		delete data;
}
void CommandMS::Command_HEALTH_CHECK_RESPONSE(Packet* p)
{
	std::unordered_map<int, int>::const_iterator got = socketM->heartbeats.find(p->header->srcCode);

	if (got != socketM->heartbeats.end())
	{
		socketM->heartbeats[p->header->srcCode] = 0;
	}

	//서버의 받은 시간 저장하기
}

void CommandMS::Command_NOTI_MATCH_REQUEST(Packet* p)
{

}
void CommandMS::Command_NOTI_MATCH_RESPONSE(Packet* p)
{

}