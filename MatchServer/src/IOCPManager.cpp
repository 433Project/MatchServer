#include "IOCPManager.h"


IOCPManager::IOCPManager()
{
	mm = new MessageManager();
}

IOCPManager::~IOCPManager()
{
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
	HANDLE* threads = new HANDLE[numOfThreads];
	for (int i = 0; i < numOfThreads; i++)
	{
		threads[i] = (HANDLE)_beginthreadex(NULL, 0, ProcessThread, (LPVOID)iocp, 0, NULL);
	}

	WaitForMultipleObjects(numOfThreads, threads, true, INFINITE);

	for (int i = 0; i < numOfThreads; i++)
	{
		if (threads[i] != INVALID_HANDLE_VALUE)
		{
			delete threads[i];
		}
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
			//closesocket;
			continue;
		}
		Packet* p = new Packet();
		mm->ReadPacket(p, ioData->buffer);
		
		//if srcType이 MS 나 RS일 경우
		//메세지큐에 넣기
		//else 
		//커맨드핸들러에게 넘기기
	}
	_endthreadex(0);
	return 0;
}