#pragma once
#include "CommandHandler.h"
#include "Protocol.h"

CommandHandler::CommandHandler()
{
}


CommandHandler::~CommandHandler()
{
}


void CommandHandler::HandleCommand(Packet packet) 
{

	switch (packet.body.command) {
		// ��Ī ��û 
	case Command::MATCH_REQUEST:

		MatchingRequest

		break;

	}
	

}