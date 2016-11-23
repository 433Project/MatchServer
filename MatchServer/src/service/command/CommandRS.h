#pragma once
#include "Protocol.h"
#include "Logger.h"

class SocketManager;
class MessageManager;

class CommandRS
{
public:
	CommandRS();
	~CommandRS();
	void CommandRSHandler(Packet* p);

private:
	//void Command_ROOM_CREATE_REQUEST(Packet* p);
	//void Command_CREATE_RESPONSE(Packet* p);

	//typedef void(CommandRS::*FuncType)(Packet* p);
	//FuncType* func;

private:
	/*int cmd = 20;
	int funcCount = 2;*/
	Logger& logger = Logger::GetInstance();
	SocketManager* socketM;
	MessageManager* msgM;
};

