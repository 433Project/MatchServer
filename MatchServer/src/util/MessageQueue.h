#pragma once
#include "Message.h"
#include <deque>


class MessageQueue
{
public:
	//---- constr
	MessageQueue();
	~MessageQueue();

	//---- service
	bool Push(Message message);
	Message Pop();
	

private: 
	deque<Message> mailbox;

};

