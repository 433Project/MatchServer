#include "MatchServer.h"

#define LISTEN_SOCKET 0

MatchServer::MatchServer()
{
	try 
	{
		mm = new MessageManager();
		packetSize = mm->packetSize;
		headerSize = mm->headSize;

		sm = new SocketManager();
	}
	catch (exception e) 
	{
	}
}

MatchServer::~MatchServer()
{
	WSACleanup();
	if (hConfigSock != INVALID_SOCKET)
		closesocket(hConfigSock);
	if (hConnSock != INVALID_SOCKET)
		closesocket(hConnSock);
	if (hsoListen != INVALID_SOCKET)
		closesocket(hsoListen);
	if(mm != nullptr)
		delete mm;
	if (sm != nullptr)
		delete sm;
}

void MatchServer::RunServer() {
	cout << "#############################################################" << endl;
	cout << "#####################=================#######################" << endl;
	cout << "#####################   Match Server  #######################" << endl;
	cout << "#####################=================#######################" << endl;
	cout << "#############################################################" << endl;

	int nErrCode = WSAStartup(MAKEWORD(2, 2), &wsd);
	if (nErrCode)
	{
		cout << "WSAStartup failed, code : " << nErrCode << endl;
		return;
	}

	//===================IOCP Creation & Make Thread Pool
	GetSystemInfo(&si);
	int numOfCPU = si.dwNumberOfProcessors;
	int numOfThreads = numOfCPU * 2;

	hCompletion = CreateNewCompletionPort(si.dwNumberOfProcessors);

	for (int i = 0; i < numOfThreads; i++)
	{
		_beginthreadex(NULL, 0, ProcessThread, (LPVOID)hCompletion, 0, NULL);
	}

	//==================Connect to Config Server
	hConfigSock = sm->GetConnectSocket("CF", confIP, confPort);	// Config Server ip, port
	if (hConfigSock == INVALID_SOCKET)
		return;

	AssociateDeviceWithCompletionPort(hCompletion, (HANDLE)hConfigSock, CONFIG_SERVER);
	IO_DATA* ov = new IO_DATA(hConfigSock);
	mm->ReceivePacket(ov);
	
	
	//==================Connect to Connection Server
	hConnSock = sm->GetConnectSocket("CS", connIP, connPort);	// Connection Server ip, port
	if (hConnSock == INVALID_SOCKET)
		return;
	cout << "Connected CS" << endl;
	AssociateDeviceWithCompletionPort(hCompletion, (HANDLE)hConnSock, CONNECTION_SERVER);

	ov = new IO_DATA(hConnSock);
	mm->ReceivePacket(ov);
	
	//=================== Listen Socket for Match Server
	hsoListen = sm->GetListenSocket(port, backlog);
	
	AssociateDeviceWithCompletionPort(hCompletion, (HANDLE)hsoListen, LISTEN_SOCKET);
	sm->AcceptEX(2);

	while (TRUE)
	{
	}
}

HANDLE MatchServer::CreateNewCompletionPort(DWORD dwNumberOfConcurrentThreads)
{
	return (CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, dwNumberOfConcurrentThreads));
}

BOOL MatchServer::AssociateDeviceWithCompletionPort(HANDLE hCompletionPort, HANDLE hDevice, DWORD dwCompletionKey)
{
	HANDLE h = CreateIoCompletionPort(hDevice, hCompletionPort, dwCompletionKey, 0);

	return(h == hCompletionPort);
}

unsigned int __stdcall MatchServer::ProcessThread(LPVOID hCompletion)
{
	MessageManager *mm = new MessageManager();
	SocketManager * sm = new SocketManager();
	HANDLE hCompletionPort = hCompletion;

	DWORD bytesTransferred;
	IO_DATA* ioData;
	ULONG_PTR	key = 0;
	
	while (TRUE)
	{
		GetQueuedCompletionStatus(
			hCompletionPort,
			&bytesTransferred,
			&key,
			(LPOVERLAPPED*)&ioData,
			INFINITE
		);

		Header* h = NULL;
		const Body* b = NULL;
		if (bytesTransferred != 0) {
			h = mm->ReadHeader(ioData->buffer);
			b = mm->ReadBody(h->length, ioData->buffer);
		}

		if (b->cmd() == COMMAND_HEALTH_CHECK) {
			char* data = mm->MakePacket((TERMINALTYPE)key, 0, COMMAND_HEALTH_CHECK, STATUS_NONE, "", "");
			mm->SendPacket(ioData->hClntSock, data);
			delete data;
		}
		else if (key == LISTEN_SOCKET) 
		{
			AssociateDeviceWithCompletionPort(hCompletionPort, (HANDLE)ioData->hClntSock, MATCHING_SERVER);
			cout << " ==> New Matching Server " << ioData->hClntSock << " connected..." << endl;
			sm->AcceptEX(1);
		}
		else if (key == CONFIG_SERVER) 
		{
			if (bytesTransferred == 0)
			{
				cout << " ==> Config Server is disconnected..." << endl;
				closesocket(ioData->hClntSock);
				continue;
			}

			if (b->cmd() == COMMAND_MS_ID)
			{
				cout << "My ID : " << b->data1()->c_str() << endl;
				char* data = mm->MakePacket(CONFIG_SERVER, 0, COMMAND_MSLIST_REQUEST, STATUS_NONE, "", "");
				mm->SendPacket(ioData->hClntSock, data);
				delete data;
			}
			else if (b->cmd() == COMMAND_MSLIST_RESPONSE)
			{
				if (b->status() == STATUS_SUCCESS)
				{
					cout << "Connecting to Matching Server(" << b->data1()->c_str() << ")" << endl;
					SOCKET s = sm->GetConnectSocket("MS", (char*)b->data2()->c_str(), port);
					if (s != INVALID_SOCKET)
						AssociateDeviceWithCompletionPort(hCompletion, (HANDLE)s, MATCHING_SERVER);
					else
						closesocket(s);
				}
			}
		}
		else if (key == CONNECTION_SERVER) 
		{
			if (bytesTransferred == 0)
			{
				cout << " ==> Connection Server(" << ioData->hClntSock << ") is disconnected..." << endl;
				closesocket(ioData->hClntSock);
				continue;
			}
		}
		else if (key == MATCHING_SERVER) 
		{
			if (bytesTransferred == 0)
			{
				cout << " ==> Matching Server("<< ioData->hClntSock <<") is disconnected..." << endl;
				closesocket(ioData->hClntSock);
				continue;
			}
		}
		
		mm->ReceivePacket(ioData);
	}
	return 0;
}