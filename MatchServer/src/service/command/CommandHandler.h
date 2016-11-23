#pragma once
#include "Protocol.h"
#include "Logger.h"
#include <WinSock2.h>
class CommandMS;
class CommandMC;
class CommandRS;
class CommandCF;
class SocketManager;
class MessageManager;

class CommandHandler
{
public:
	CommandHandler();
	~CommandHandler();
	void ProcessCommand(Packet* p);
	void ProcessListen(SOCKET s, char* bytes);

private:
	int handlerCount = 4;
	CommandMS* ms;
	CommandMC* mc;
	CommandRS* rs;
	CommandCF* cf;
	SocketManager* socketM;
	MessageManager* msgM;
	Logger& logger = Logger::GetInstance();
	
};

