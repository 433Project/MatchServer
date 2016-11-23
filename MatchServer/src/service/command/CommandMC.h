#pragma once
#include "Protocol.h"
#include "Logger.h"

class SocketManager;
class MessageManager;

class CommandMC
{
public:
	CommandMC();
	~CommandMC();
	void CommandMCHandler(Packet* p);

private:
	void Command_MATCH_REQUEST(Packet* p);
	void Command_MATCH_RESPONSE(Packet* p);

	typedef void(CommandMC::*FuncType)(Packet* p);
	FuncType* func;

private:
	int cmd = 20;
	int funcCount = 2;

	Logger& logger = Logger::GetInstance();
	SocketManager* socketM;
	MessageManager* msgM;
};

