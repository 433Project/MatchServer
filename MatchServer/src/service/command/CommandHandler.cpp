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

	switch (p->header->srcCode) {
	case CONFIG_SERVER:
		cf->CommandCFHandler(p);
		break;
	case MATCHING_SERVER:
		break;
	case MATCHING_CLIENT:
		break;
	case ROOM_SERVER:
		break;
	default:
		break;
	}
}
