#pragma once
#include "Protocol.h"
#include <deque>

class MessageQueue
{
public:
	//---- constr
	~MessageQueue();
	static MessageQueue* GetInstance();

	//---- service
	bool Push(Packet* packet);
	Packet* Pop();
	bool IsEmpty();
	int Length();
	
private: 
	deque<Packet*> queue;
	static MessageQueue* messageQueue;

	MessageQueue();
};

