#pragma once
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

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

inline const char **EnumNamesCOMPLETIONKEY() {
	static const char *names[] = { "LISTEN", "CONFIG", "CONNECTION", "MATCHING", nullptr };
	return names;
}

class IOCPManager
{
public:
	static IOCPManager* GetInstance();
	~IOCPManager();
	void Start();
	BOOL AssociateDeviceWithCompletionPort(HANDLE handle, DWORD completionKey);

protected:
	IOCPManager();

private:
	HANDLE CreateNewCompletionPort(DWORD numberOfConcurrentThreads);	
	static unsigned __stdcall ProcessThread(void* iocp);

private:
	static IOCPManager* instance;
	HANDLE iocp;
	HANDLE* threads;
	int numOfThreads;
	static const int packetSize = 100;

};

