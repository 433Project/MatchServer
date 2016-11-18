
#pragma once
#include "Client.h"
#include "Protocol.h"

// Command : 
class CommandRoomCreateRequest 
{

public:

	void HandleCommand(Client c1, Client c2) 
	{
		
		Header header = Header(0, TERMINALTYPE::MATCHING_SERVER, 0, TERMINALTYPE::ROOM_SERVER, 0);
		// generate packet
		//Packet packet = Packet();

		// send 
	}

};