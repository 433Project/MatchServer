#include "CommandCF.h"
#include "MessageManager.h"
#include "SocketManager.h"

Logger& logg = Logger::GetInstance();
AppConfig config = AppConfig::GetInstance();
MessageManager* msg = new MessageManager();
SocketManager* socketM = SocketManager::GetInstance();

CommandCF::CommandCF()
{
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
}

void CommandCF::CommandCFHandler(Packet* p)
{
	(this->*func[p->body->cmd() - this->cmd])(p);
}

void CommandCF::Command_MSLIST_REQUEST (Packet* p) 
{
	//This command will never get received.
	//Because MS sends it to Config Server
	logg.ERROR("MS will be never received this command!");
}

void CommandCF::Command_MSLIST_RESPONSE (Packet* p)
{
	int id = atoi(p->body->data1()->c_str());
	char* ip = (char*)p->body->data2()->c_str();

	logg.INFO("New Matching Server");
	socketM->CreateSocket(MATCHING, ip, id);
}

void CommandCF::Command_MS_ID (Packet* p)
{
	//Appconfig에 id 저장하기 p->body->data1()->c_str();
	logg.INFO("Get ID");
	char* data = new char[socketM->packetSize];
	msg->MakePacket(data, CONFIG_SERVER, 0, COMMAND_MSLIST_REQUEST, STATUS_NONE, "", "");
	socketM->SendPacket(socketM->cfSocket, data);
	
	if(data != nullptr)
		delete data;
}