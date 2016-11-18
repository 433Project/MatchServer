#include "MessageQueue.h"

MessageQueue::MessageQueue()
{
	InitializeCriticalSectionAndSpinCount(&this->CriticalSection, 0);
}

MessageQueue::~MessageQueue()
{
	DeleteCriticalSection(&this->CriticalSection);
}

MessageQueue* MessageQueue::messageQueue = nullptr;
// get message queue singleton instance
MessageQueue* MessageQueue::GetInstance() 
{
	if (messageQueue == NULL) 
	{
		messageQueue = new MessageQueue();
	}
	return messageQueue;
}

Packet* MessageQueue::Pop() 
{
	EnterCriticalSection(&this->CriticalSection);
	Packet* msg = this->queue.front();

	this->messageQueue->queue.pop_front();
	LeaveCriticalSection(&this->CriticalSection);
	return msg;
}

bool MessageQueue::Push(Packet* message) 
{
	EnterCriticalSection(&this->CriticalSection);
	this->messageQueue->queue.push_back(message);
	LeaveCriticalSection(&this->CriticalSection);
	return true;
}

// true: empty, false: not 
bool MessageQueue::IsEmpty() 
{
	if (this->messageQueue->queue.size() !=0 ) 
	{
		return this->messageQueue->queue.empty();	
	}
	return 0;
}

//  return MessageQueue length 
int MessageQueue::Length() 
{
	return this->messageQueue->queue.size();
}