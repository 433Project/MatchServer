#include "CommandHandler.h"

CommandHandler::CommandHandler()
{
	ms = new CommandMS();
	mc = new CommandMC();
	cf = new CommandCF();
	rs = new CommandRS();
}


CommandHandler::~CommandHandler()
{
	if (ms != nullptr)
		delete ms;
	if (mc != nullptr)
		delete mc;
	if (cf != nullptr)
		delete cf;
	if (rs != nullptr)
		delete rs;
}

void CommandHandler::ProcessCommand(Packet* p)
{
	if (p->body->cmd() >= 40) 
	{

	}
	else if (p->body->cmd() >= 30) 
	{
		cf->CommandCFHandler(p);
	}
	else if (p->body->cmd() >= 20)
	{

	}
	else if (p->body->cmd() >= 10)
	{

	}
}
