#include "CommandRS.h"
#include "MessageQueue.h"

CommandRS::CommandRS()
{
	msgQ = MessageQueue::GetInstance();
}

CommandRS::~CommandRS()
{
}

void CommandRS::CommandRSHandler(Packet* p)
{
	msgQ->Push(p);
	
}

//void CommandRS::Command_ROOM_CREATE_REQUEST(Packet* p)
//{
//	
//}
//
//void CommandRS::Command_CREATE_RESPONSE(Packet* p)
//{
//	
//}