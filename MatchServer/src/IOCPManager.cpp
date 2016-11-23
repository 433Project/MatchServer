#include "IOCPManager.h"
#include <process.h>
#include "MessageQueue.h"
#include "MessageManager.h"
#include "Logger.h"
#include "CommandHandler.h"

IOCPManager* IOCPManager::instance = nullptr;

IOCPManager::IOCPManager()
{
}

IOCPManager::~IOCPManager()
{
	for (int i = 0; i < numOfThreads; i++)
	{
		if (threads[i] != INVALID_HANDLE_VALUE)
		{
			delete threads[i];
		}
	}

	delete iocp;
}


IOCPManager* IOCPManager::GetInstance()
{
	if (instance == nullptr)
		instance = new IOCPManager();
	return instance;
}


void IOCPManager::Start()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	int numOfCPU = si.dwNumberOfProcessors;
	numOfThreads = numOfCPU * 2;

	//Create IOCP
	iocp = CreateNewCompletionPort(si.dwNumberOfProcessors);
	
	//Create Thread Pool
	threads = new HANDLE[numOfThreads];
	for (int i = 0; i < numOfThreads; i++)
	{
		threads[i] = (HANDLE)_beginthreadex(NULL, 0, ProcessThread, (LPVOID)iocp, 0, NULL);
	}

}

HANDLE IOCPManager::CreateNewCompletionPort(DWORD numberOfConcurrentThreads)
{
	return (CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, numberOfConcurrentThreads));
}

BOOL IOCPManager::AssociateDeviceWithCompletionPort(HANDLE handle, DWORD completionKey)
{
	HANDLE h = CreateIoCompletionPort(handle, iocp, completionKey, 0);

	return(h == iocp);
}

unsigned __stdcall IOCPManager::ProcessThread(void* iocp)
{
	Logger& logger = Logger::GetInstance();
	CommandHandler* cmdHandler = new CommandHandler();
	MessageManager* msgM = new MessageManager();

	HANDLE completionPort = iocp;

	DWORD bytesTransferred;
	IO_DATA* ioData;
	ULONG_PTR completionKey = 0;
	while (TRUE)
	{
		GetQueuedCompletionStatus(
			completionPort,
			&bytesTransferred,
			&completionKey,
			(LPOVERLAPPED*)&ioData,
			INFINITE
		);

		if (completionKey == LISTEN)
		{
			logger.Info("Accepted");
			cmdHandler->ProcessListen(ioData->hClntSock, ioData->buffer);
			continue;
		}

		if (bytesTransferred == 0) 
		{
			logger.Info("disconnected with socket ", ioData->hClntSock);
			closesocket(ioData->hClntSock);
			continue;
		}

		Packet* p = new Packet();
		msgM->ReadPacket(p, ioData->buffer);
		
		
		if (completionKey == CONFIG || completionKey == CONNECTION || completionKey == MATCHING)
		{
			cmdHandler->ProcessCommand(p);
		}
		else 
		{
			logger.Error("Unkwon Completion key", completionKey);
		}
		
		ioData->buffer = new char[packetSize];
		DWORD flag = MSG_PUSH_IMMEDIATE;
		WSABUF wsaBuf;
		wsaBuf.buf = ioData->buffer;
		wsaBuf.len = packetSize;
		WSARecv(ioData->hClntSock, &wsaBuf, 1, NULL, &flag, ioData, NULL);
	}

	if(msgM != nullptr)
		delete msgM;
	if (cmdHandler != nullptr)
		delete cmdHandler;
	_endthreadex(0);
	return 0;
}