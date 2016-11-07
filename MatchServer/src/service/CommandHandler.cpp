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
		// ¸ÅÄª ¿äÃ» 
	case Command::MATCH_REQUEST:

		MatchingRequest

		break;

	}
	

}