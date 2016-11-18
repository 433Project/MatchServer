#pragma once
#include <winsock2.h>
#include <process.h>
#include "Logger.h"
#include "MessageManager.h"

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

struct IO_DATA : OVERLAPPED
{
	char* buffer;		
	SOCKET hClntSock;

	IO_DATA(SOCKET sock)

	{
		memset(this, 0, sizeof(*this));
		hClntSock = sock;
	}
};

enum COMPLETIONKEY : int 
{
	LISTEN = 0,
	CONFIG,
	CONNECTION,
	MATCHING
};

class IOCPManager
{
protected:
	IOCPManager();
	~IOCPManager();
	
public:
	static IOCPManager* GetInstance();
	void Start();
	BOOL AssociateDeviceWithCompletionPort(HANDLE handle, DWORD completionKey);

private:
	HANDLE CreateNewCompletionPort(DWORD numberOfConcurrentThreads);	
	static unsigned __stdcall ProcessThread(void* iocp);

private:
	static IOCPManager* instance;
	static MessageManager* mm;

	HANDLE iocp;
	int numOfThreads;
};

