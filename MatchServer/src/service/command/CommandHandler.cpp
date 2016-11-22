#include "CommandHandler.h"
#include "CommandMS.h"
#include "CommandMC.h"
#include "CommandCF.h"
#include "CommandRS.h"
#include "MessageManager.h"
#include "SocketManager.h"

CommandHandler::CommandHandler()
{
	socketM = SocketManager::GetInstance();
	msgM = new MessageManager();
	ms = new CommandMS();
	mc = new CommandMC();
	cf = new CommandCF();
	rs = new CommandRS();
}


CommandHandler::~CommandHandler()
{
	if (msgM != nullptr)
		delete msgM;
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
	if (p->body->cmd() == COMMAND_HEALTH_CHECK_REQUEST)
	{
		char* data = new char[100];
		msgM->MakePacket(data, p->header->srcType, p->header->srcCode, COMMAND_HEALTH_CHECK_RESPONSE, STATUS_NONE, "", "");
	
		switch (p->header->srcType)
		{
		case CONNECTION_SERVER:
			socketM->SendPacket(socketM->csSocket, data);
			break;
		case CONFIG_SERVER:
			socketM->SendPacket(socketM->cfSocket, data);
			break;
		case MATCHING_SERVER:
			socketM->SendPacket(socketM->cfSocket, data);
			break;
		default:
			logger.Error("received HEALTH_CHECK_REQUEST from ", p->header->srcType);
			break;
		}
		
		if (data != nullptr)
		delete data;
	}
	else 
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
			logger.Error("received Message from ", p->header->srcType);
			break;
		}
	}
	
}
