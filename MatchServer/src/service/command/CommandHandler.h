#pragma once
#include "CommandCF.h"
#include "CommandMS.h"
#include "CommandMC.h"
#include "CommandRS.h"

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

