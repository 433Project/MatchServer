#include "CommandMS.h"
#include "SocketManager.h"
#include "MessageManager.h"

CommandMS::CommandMS()
{
	msgM = new MessageManager();
	socketM = SocketManager::GetInstance();

	/*func = new FuncType[funcCount];
	func[0] = &CommandMS::Command_NOTI_MATCH_REQUEST;
	func[1] = &CommandMS::Command_NOTI_MATCH_RESPONSE;*/
}


CommandMS::~CommandMS()
{
	//for (int i = 0; i < funcCount; i++)
	//{
	//	delete &func[i];
	//}
	//delete func;
	//if (msgM != nullptr)
	//	delete msgM;
}

void CommandMS::CommandMSHandler(Packet* p)
{
	if (p->body->cmd() == COMMAND_HEALTH_CHECK_REQUEST)
		Command_HEALTH_CHECK_REQUEST(p);
	else if (p->body->cmd() == COMMAND_HEALTH_CHECK_RESPONSE)
		Command_HEALTH_CHECK_RESPONSE(p);
	else
		;
	//메세지 큐에 넣기
}

void CommandMS::Command_HEALTH_CHECK_REQUEST(Packet* p)
{
	char* data = new char[100];
	logger.Info("error check 해야하지 않을가? id = ", config.GetConfig<json>("ID"));
	msgM->MakePacket(data, p->header->srcType, p->header->srcCode, COMMAND_HEALTH_CHECK_RESPONSE, STATUS_NONE, "", "", config.GetConfig<json>("ID"));
	socketM->SendPacket(socketM->cfSocket, data);
	if (data != nullptr)
		delete data;
}
void CommandMS::Command_HEALTH_CHECK_RESPONSE(Packet* p)
{
	//서버의 시간 업데이트 레이턴시
}

//void CommandMS::Command_NOTI_MATCH_REQUEST(Packet* p)
//{
//
//}
//void CommandMS::Command_NOTI_MATCH_RESPONSE(Packet* p)
//{
//
//}