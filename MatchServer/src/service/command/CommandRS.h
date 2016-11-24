#pragma once
#include "Protocol.h"
#include "Logger.h"

class MessageQueue;

class CommandRS
{
public:
	CommandRS();
	~CommandRS();
	void CommandRSHandler(Packet* p);

private:
	//void Command_ROOM_CREATE_REQUEST(Packet* p);
	//void Command_CREATE_RESPONSE(Packet* p);

private:
	Logger& logger = Logger::GetInstance();
	MessageQueue* msgQ;
};

