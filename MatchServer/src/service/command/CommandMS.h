#pragma once
#include "Protocol.h"
#include "AppConfig.h"

class SocketManager;
class MessageManager;
class MessageQueue;

class CommandMS
{
public:
	CommandMS();
	~CommandMS();
	void CommandMSHandler(Packet* p);

private:
	void Command_HEALTH_CHECK_REQUEST(Packet* p);
	void Command_HEALTH_CHECK_RESPONSE(Packet* p);
	void Command_NOTI_MATCH_REQUEST(Packet* p);
	void Command_NOTI_MATCH_RESPONSE(Packet* p);

private:
	Logger& logger = Logger::GetInstance();
	AppConfig& config = AppConfig::GetInstance();
	//ServerHolder& servers = ServerHolder::GetInstance();

	SocketManager* socketM;
	MessageManager* msgM;
	MessageQueue* msgQ;
};

