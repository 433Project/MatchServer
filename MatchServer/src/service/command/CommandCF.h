#pragma once
#include "Protocol.h"
#include "AppConfig.h"

class SocketManager;
class MessageManager;

class CommandCF
{
public:
	CommandCF();
	~CommandCF();
	void CommandCFHandler(Packet* p);

private:
	void Command_MSLIST_REQUEST (Packet* p);
	void Command_MSLIST_RESPONSE (Packet* p);
	void Command_MS_ID (Packet* p);

	typedef void(CommandCF::*FuncType)(Packet* p);
	FuncType* func;

private:
	int cmd = 30;
	int funcCount = 3;
	Logger& logger = Logger::GetInstance();
	AppConfig& config = AppConfig::GetInstance();

	SocketManager* socketM;
	MessageManager* msgM ;
};

