#pragma once
#include "Message.h"
#include <deque>


class MessageQueue
{
public:
	//---- constr
	MessageQueue();
	~MessageQueue();
	//---- 
	static MessageQueue* GetInstance();

	//---- service
	bool Push(Message message);
	Message Pop();
	int Length();
	bool IsEmpty();

private: 
	deque<Message> mailbox;
	static MessageQueue* instance;

};

