#pragma once
#include "Protocol.h"

class CommandHandler
{
public:
	CommandHandler();
	~CommandHandler();

	void HandleCommand(Packet packet);

private:



};

