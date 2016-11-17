#include "MessageQueue.h"

MessageQueue::MessageQueue()
{

}

MessageQueue::~MessageQueue()
{
}

MessageQueue* MessageQueue::messageQueue = nullptr;
// get message queue singleton instance
MessageQueue* MessageQueue::GetInstance() {
	if (messageQueue == NULL) {
		messageQueue = new MessageQueue();
	}
	return messageQueue;
}

Packet* MessageQueue::Pop() {
	Packet* msg = this->queue.front();

	this->messageQueue->queue.pop_front();

	return msg;
}

bool MessageQueue::Push(Packet* message) {
	this->messageQueue->queue.push_back(message);
	
	return true;
}

// true: empty, false: not 
bool MessageQueue::IsEmpty() {
	if (this->messageQueue->queue.size() !=0 ) {
		return this->messageQueue->queue.empty();	
	}
	return 0;
}

//  return MessageQueue length 
int MessageQueue::Length() {
	return this->messageQueue->queue.size();
}