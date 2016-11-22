#pragma once
#include "Protocol.h"
class CommandMS;
class CommandMC;
class CommandRS;
class CommandCF;

class CommandHandler
{
public:
	CommandHandler();
	~CommandHandler();
	void ProcessCommand(Packet* p);

private:
	CommandMS* ms;
	CommandMC* mc;
	CommandRS* rs;
	CommandCF* cf;
	int handlerCount = 4;
	
};

