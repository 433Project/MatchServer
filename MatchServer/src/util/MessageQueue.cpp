#include "MessageQueue.h"

MessageQueue::MessageQueue()
{
	
}

MessageQueue::~MessageQueue()
{
}

MessageQueue* MessageQueue::instance = nullptr;
MessageQueue* MessageQueue::GetInstance() {

	if (instance == nullptr) {
		instance = new MessageQueue();
	}
	return instance;
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


// true: empty, false: has elements
bool MessageQueue::IsEmpty() {
	return this->mailbox.empty();
		
}

int MessageQueue::Length() {
	return this->mailbox.size();
}
