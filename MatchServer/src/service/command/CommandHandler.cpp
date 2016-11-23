#pragma once
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
	switch (p->header->srcType) {
	case CONFIG_SERVER:
		cf->CommandCFHandler(p);
		break;
	case MATCHING_SERVER:	//메세지 큐에 넣어주기
		ms->CommandMSHandler(p);
		break;
	case MATCHING_CLIENT:
		mc->CommandMCHandler(p);
		break;
	case ROOM_SERVER:		//메세지 큐에 넣어주기
		rs->CommandRSHandler(p);
		break;
	default:
		//logger.Error("received Message from ", p->header->srcType);
		break;
	}	
}

void CommandHandler::ProcessListen(SOCKET s, char* bytes)
{
	Header* h = new Header();
	msgM->BytesToHeader(bytes, h);
	socketM->AcceptMS(s, h->srcCode);
}

