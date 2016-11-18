#pragma once
#include "Protocol.h"
#include <deque>
#include <Windows.h>
#include <WinBase.h>

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
	
	CRITICAL_SECTION CriticalSection;

	MessageQueue();
};

