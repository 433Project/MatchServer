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
	//Body�� �о HEALTH_CHECK���� MSLIST_RESPONSE���������� process
}

void ProcessManager::ProcessConnectionServer(char* buf)
{
	//Header* h = mManager->CharPtrToHeader(buf);

}

void ProcessManager::ProcessMatchingServer(char* buf)
{

}