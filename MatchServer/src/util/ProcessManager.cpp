#include "ProcessManager.h"
#include "MessageManager.h"

MessageManager* mManager;
ProcessManager::ProcessManager()
{
	mManager = new MessageManager();
}


ProcessManager::~ProcessManager()
{
}

void ProcessManager::ProcessConfigServer(Body* body) 
{
	//Body�� �о HEALTH_CHECK���� MSLIST_RESPONSE���������� process
}

void ProcessManager::ProcessConnectionServer(Body* body)
{
	//Header* h = mManager->CharPtrToHeader(buf);

}

void ProcessManager::ProcessMatchingServer(Body* body)
{

}