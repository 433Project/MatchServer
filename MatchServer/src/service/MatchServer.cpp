#include "MatchServer.h"

MessageManager* mm;
SocketManager* sm;
MatchServer::MatchServer()
{
	mm = new MessageManager();
	packetSize = mm->packetSize;
	headerSize = mm->headSize;

	sm = new SocketManager();
}

MatchServer::~MatchServer()
{
	WSACleanup();
	closesocket(hConfigSock);
	closesocket(hConnSock);
	closesocket(hsoListen);
	delete mm;
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
	hConfigSock = sm->GetConnectSocket(confIP, confPort);	// Config Server ip, port
	if (hConfigSock == INVALID_SOCKET)
		return;

	AssociateDeviceWithCompletionPort(hCompletion, (HANDLE)hConfigSock, KEY_CONFIG_SERVER);
	IO_DATA* ov = new IO_DATA(hConfigSock);
	mm->ReceivePacket(ov);

	//==================Connect to Connection Server
	hConnSock = sm->GetConnectSocket(connIP, connPort);	// Connection Server ip, port
	if (hConnSock == INVALID_SOCKET)
		return;
	
	AssociateDeviceWithCompletionPort(hCompletion, (HANDLE)hConnSock, KEY_CONNECTION_SERVER);
	ov = new IO_DATA(hConnSock);
	mm->ReceivePacket(ov);

	char* data = mm->MakePacket(ROOM_MANAGER, 0, Command_ROOM_CREATE_REQUEST, Status_NONE, "");
	mm->SendPacket(hConnSock, data);
	
	//=================== Listen Socket for Match Server
	hsoListen = sm->GetListenSocket(port, backlog);
	
	AssociateDeviceWithCompletionPort(hCompletion, (HANDLE)hsoListen, KEY_LISTEN_SOCKET);
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
		
		if (key == KEY_LISTEN_SOCKET) 
		{
			AssociateDeviceWithCompletionPort(hCompletionPort, (HANDLE)ioData->hClntSock, KEY_MATCH_SERVER);
			cout << " ==> New Matching Server " << ioData->hClntSock << " connected..." << endl;
			struct sockaddr_in sin;
			int len = sizeof(sin);
			if (getsockname(ioData->hClntSock, (struct sockaddr *)&sin, &len) != -1)
				cout << inet_ntoa(sin.sin_addr) << endl;
		}
		else if (key == KEY_CONFIG_SERVER) 
		{
			if (bytesTransferred == 0)
			{
				cout << " ==> Config Server is disconnected..." << endl;
				closesocket(ioData->hClntSock);
				continue;
			}
			if (b->cmd() == Command_MS_ID) 
			{
				cout << "My ID : " << b->data()->c_str()<< endl;
				char* data = mm->MakePacket(CONFIG_SERVER, 0, Command_MSLIST_REQUEST, Status_NONE, "");
				mm->SendPacket(ioData->hClntSock, data);
			}
			else if (b->cmd() == Command_MSLIST_RESPONSE) 
			{
				if (b->status() == Status_SUCCESS)
				{
					sm->GetConnectSocket((char*)b->data()->c_str(), 12000);
					sm->AcceptEX(1);
				}
			}
			
		}
		else if (key == KEY_CONNECTION_SERVER) 
		{
			if (bytesTransferred == 0)
			{
				cout << " ==> Connection Server(" << ioData->hClntSock << ") is disconnected..." << endl;
				closesocket(ioData->hClntSock);
				continue;
			}
		}
		else if (key == KEY_MATCH_SERVER) 
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