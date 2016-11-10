#pragma once
#include "Message.h"
#include "Packet_generated.h"

class MessageConverter
{
public:
	MessageConverter();

	Message Convert(Body body);

	~MessageConverter();
};

