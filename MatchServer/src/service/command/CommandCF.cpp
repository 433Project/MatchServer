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
	//Because Config sends it to MS
	logger.Error("MS will be never received this command from Config! - Command_HEALTH_CHECK_RESPONSE");
}

void CommandCF::Command_MSLIST_REQUEST (Packet* p) 
{
	//This command will never get received.
	//Because MS sends it to Config Server
	logger.Error("MS will be never received this command!-Command_MSLIST_REQUEST");
}

void CommandCF::Command_MSLIST_RESPONSE (Packet* p)
{
	int id = atoi(p->body->data1()->c_str());
	char* ip = (char*)p->body->data2()->c_str();
	logger.Info(" Command_MSLIST_RESPONSE ip : ", ip);
	logger.Info("Connecting to  MS");
	socketM->CreateSocket(MATCHING, ip, id);

	char* data = new char[sizeof(Header)];
	msgM->HeaderToBytes(data, MATCHING_SERVER, id, config.GetConfig<json>("ID"));
	socketM->SendPacket(socketM->msList[id], data);
	logger.Info("Send header to id : ", id);
	if (data != nullptr)
		delete data;

	//서버추가하기
}

void CommandCF::Command_MS_ID (Packet* p)
{
	int id = atoi(p->body->data1()->c_str());
	if (id != 0)
	{
		config.GetAppConfig()["ID"] = id;
		logger.Info("Server id : ", id);
		char* data = new char[socketM->packetSize];
		msgM->MakePacket(data, CONFIG_SERVER, 0, COMMAND_MSLIST_REQUEST, STATUS_NONE, "", "");
		socketM->SendPacket(socketM->cfSocket, data);

		if (data != nullptr)
			delete data;
	}
	else
		logger.Error("Convert string to int fail", p->body->data1()->c_str());
	
}