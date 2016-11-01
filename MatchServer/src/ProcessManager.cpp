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

void ProcessManager::ProcessConfigServer(char* buf) 
{
	//Body를 읽어서 HEALTH_CHECK인지 MSLIST_RESPONSE인지에따라 process
}

void ProcessManager::ProcessConnectionServer(char* buf)
{
	//Header* h = mManager->CharPtrToHeader(buf);

}

void ProcessManager::ProcessMatchingServer(char* buf)
{

}