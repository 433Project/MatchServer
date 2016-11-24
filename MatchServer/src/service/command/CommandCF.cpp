#include "CommandCF.h"
#include "SocketManager.h"
#include "MessageManager.h"
//#include "ServerHolder.h"

CommandCF::CommandCF()
{
	msgM = new MessageManager();
	socketM = SocketManager::GetInstance();

	func = new FuncType[funcCount];
	func[0] = &CommandCF::Command_MSLIST_REQUEST;
	func[1] = &CommandCF::Command_MSLIST_RESPONSE;
	func[2] = &CommandCF::Command_MS_ID;
}

CommandCF::~CommandCF()
{
	for (int i = 0; i < funcCount; i++)
	{
		delete &func[i];
	}
	delete func;
	if (msgM != nullptr)
		delete msgM;
}

void CommandCF::CommandCFHandler(Packet* p)
{
	if (p->body->cmd() == COMMAND_HEALTH_CHECK_REQUEST)
		Command_HEALTH_CHECK_REQUEST(p);
	else if (p->body->cmd() == COMMAND_HEALTH_CHECK_RESPONSE)
		Command_HEALTH_CHECK_RESPONSE(p);
	else
		(this->*func[p->body->cmd() - this->cmd])(p);
}

void CommandCF::Command_HEALTH_CHECK_REQUEST(Packet* p)
{
	char* data = new char[100];
	msgM->MakePacket(data, p->header->srcType, p->header->srcCode, COMMAND_HEALTH_CHECK_RESPONSE, STATUS_NONE, "", "");
	socketM->SendPacket(socketM->cfSocket, data);
	if (data != nullptr)
		delete data;
}
void CommandCF::Command_HEALTH_CHECK_RESPONSE(Packet* p)
{
	//This command will never get received.
	//Because MS sends it to Config
	logger.Error("MS will be never received this command from Config Server! - Command_HEALTH_CHECK_RESPONSE");
}

void CommandCF::Command_MSLIST_REQUEST (Packet* p) 
{
	//This command will never get received.
	//Because MS sends it to Config Server
	logger.Error("MS will be never received this command from Config Server! - Command_MSLIST_REQUEST");
}

void CommandCF::Command_MSLIST_RESPONSE (Packet* p)
{
	int id = atoi(p->body->data1()->c_str());
	char* ip = (char*)p->body->data2()->c_str();
	logger.Info("Command_MSLIST_RESPONSE (ip : ", ip, ", id : ", id, ")");
	socketM->CreateSocket(MATCHING, ip, id);
	
	if(socketM->serverID != 0)
	{
		char* data = new char[sizeof(Header)];
		msgM->HeaderToBytes(data, MATCHING_SERVER, id, socketM->serverID);
		socketM->SendPacket(socketM->msList[id], data);
		if (data != nullptr)
			delete data;
	}
	else
	{
		logger.Error("Doesn't exist ServerID");
	}
	//서버추가하기
}

void CommandCF::Command_MS_ID (Packet* p)
{
	int id = atoi(p->body->data1()->c_str());
	logger.Info("Command_MS_ID (id : ", id, ")");
	if (id != 0)
	{
		socketM->serverID = id;
		char* data = new char[socketM->packetSize];
		msgM->MakePacket(data, CONFIG_SERVER, 0, COMMAND_MSLIST_REQUEST, STATUS_NONE, "", "");
		socketM->SendPacket(socketM->cfSocket, data);

		if (data != nullptr)
			delete data;
	}
	else
		logger.Error("Wrong value Server ID", p->body->data1()->c_str());
	
}