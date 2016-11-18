#pragma once
#include <winsock2.h>
#include <process.h>
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
	static IOCPManager* Instance();
	void Start();
	BOOL AssociateDeviceWithCompletionPort(HANDLE handle, DWORD completionKey);

private:
	HANDLE CreateNewCompletionPort(DWORD numberOfConcurrentThreads);	
	static unsigned __stdcall ProcessThread(void* iocp);

private:
	HANDLE iocp;
	int numOfThreads;
	static IOCPManager* instance;
};

