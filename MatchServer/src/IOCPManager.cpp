#include "IOCPManager.h"
#include "Logger.h"
#include "SocketManager.h"

IOCPManager* IOCPManager::instance = 0;

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
	if (instance == 0)
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
	SocketManager* socket = SocketManager::GetInstance();

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

		if (bytesTransferred == 0) 
		{
			logger.Info("disconnected with socket " + ioData->hClntSock);
			closesocket(ioData->hClntSock);
			continue;
		}

		Packet* p = new Packet();
		msgM->ReadPacket(p, ioData->buffer);
			
		if (p->body->cmd() == COMMAND_HEALTH_CHECK_REQUEST)
		{
			char* data = new char[100];
			msgM->MakePacket(data, p->header->srcType, p->header->srcCode, COMMAND_HEALTH_CHECK_RESPONSE, STATUS_NONE, "", "");
			socket->SendPacket(ioData->hClntSock, data);
			if (data != nullptr)
				delete data;
		}
		else
			cmdHandler->ProcessCommand(p);

		socket->ReceivePacket(ioData->hClntSock, ioData);
	}

	if(msgM != nullptr)
		delete msgM;

	_endthreadex(0);
	return 0;
}