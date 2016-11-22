#include "CommandCF.h"
#include <iostream>
#include "SocketManager.h"
#include"MessageManager.h"

CommandCF::CommandCF()
{
	msgM = new MessageManager();

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
	(this->*func[p->body->cmd() - this->cmd])(p);
}

void CommandCF::Command_MSLIST_REQUEST (Packet* p) 
{
	//This command will never get received.
	//Because MS sends it to Config Server
	logger.Error("MS will be never received this command!");
}

void CommandCF::Command_MSLIST_RESPONSE (Packet* p)
{
	int id = atoi(p->body->data1()->c_str());
	char* ip = (char*)p->body->data2()->c_str();

	logger.Info("New Matching Server");
	socketM->CreateSocket(MATCHING, ip, id);
}

void CommandCF::Command_MS_ID (Packet* p)
{
	logger.Info("Get ID");
	int id = atoi(p->body->data1()->c_str());
	if (id != 0)
	{
		config.GetAppConfig()["MyID"] = id;
		char* data = new char[socketM->packetSize];
		msgM->MakePacket(data, CONFIG_SERVER, 0, COMMAND_MSLIST_REQUEST, STATUS_NONE, "", "");
		socketM->SendPacket(socketM->cfSocket, data);

		if (data != nullptr)
			delete data;
	}
	else
		logger.Error("Convert string to int fail", p->body->data1()->c_str());
	
}