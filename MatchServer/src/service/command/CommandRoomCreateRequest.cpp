
#pragma once
#include "Client.h"
#include "Protocol.h"

class CommandRoomCreateRequest {


public:

	void HandleCommand(Client c1, Client c2) {
		
		Header header = Header(0, SrcDstType::MATCHING_SERVER, 0, SrcDstType::);
		// generate packet
		Packet packet = Packet();

		// send 
	}

};