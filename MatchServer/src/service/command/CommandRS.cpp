#include "CommandRS.h"
#include "SocketManager.h"
#include "MessageManager.h"


CommandRS::CommandRS()
{
	msgM = new MessageManager();
	socketM = SocketManager::GetInstance();

	/*func = new FuncType[funcCount];
	func[0] = &CommandRS::Command_ROOM_CREATE_REQUEST;
	func[1] = &CommandRS::Command_CREATE_RESPONSE;*/
}

CommandRS::~CommandRS()
{
	//for (int i = 0; i < funcCount; i++)
	//{
	//	delete &func[i];
	//}
	//delete func;
	//if (msgM != nullptr)
	//	delete msgM;
}

void CommandRS::CommandRSHandler(Packet* p)
{
	//메세지 큐에 넣기
	//(this->*func[p->body->cmd() - this->cmd])(p);
}

//void CommandRS::Command_ROOM_CREATE_REQUEST(Packet* p)
//{
//	//이건 받을수 없어
//}
//
//void CommandRS::Command_CREATE_RESPONSE(Packet* p)
//{
//	char* data = new char[100];
//	if(p->body->status() == STATUS_SUCCESS)
//	{
//		msgM->MakePacket(data, p->header->srcType, p->header->srcCode, COMMAND_HEALTH_CHECK_RESPONSE, STATUS_NONE, "", "");
//	}
//	else 
//	{
//
//	}
//
//	socketM->SendPacket(socketM->cfSocket, data);
//	if (data != nullptr)
//		delete data;
//}