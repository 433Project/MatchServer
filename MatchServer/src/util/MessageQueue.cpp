#include "MessageQueue.h"

MessageQueue::MessageQueue()
{
}


MessageQueue::~MessageQueue()
{
}

Message MessageQueue::Pop() {

	Message msg = this->mailbox.front();

	this->mailbox.pop_front();

	return msg;
}

bool MessageQueue::Push(Message message) {

	this->mailbox.push_back(message);
	
	return true;
}
