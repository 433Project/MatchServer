#include "MatchServer.h"

MessageManager* mm;

MatchServer::MatchServer()
{
	mm = new MessageManager();
}

MatchServer::~MatchServer()
{
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
	hConfigSock = GetConnectSocket(confIP, confPort);	// Config Server ip, port
	if (hConfigSock == INVALID_SOCKET)
		return;

	AssociateDeviceWithCompletionPort(hCompletion, (HANDLE)hConfigSock, CONFIG_SERVER);
	LPPER_IO_DATA ov = new PER_IO_DATA(hConfigSock);
	mm->ReceivePacket(ov);
	
	//==================Connect to Connection Server
	hConnSock = GetConnectSocket(connIP, connPort);	// Connection Server ip, port
	if (hConnSock == INVALID_SOCKET)
		return;
	
	AssociateDeviceWithCompletionPort(hCompletion, (HANDLE)hConnSock, CONNECTION_SERVER);
	ov = new PER_IO_DATA(hConnSock);
	mm->ReceivePacket(ov);
	
	//=================== Listen Socket for Match Server
	hsoListen = GetListenSocket(port, backlog);
	
	bool a = AssociateDeviceWithCompletionPort(hCompletion, (HANDLE)hsoListen, LISTEN_SOCKET);
	AcceptEX(hsoListen, 2);

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

PVOID MatchServer::GetSockExtAPI(SOCKET sock, GUID guidFn)
{
	PVOID pfnEx = NULL;
	GUID guid = guidFn;
	DWORD dwBytes = 0;

	LONG lRet = ::WSAIoctl
	(
		sock,									//Socket
		SIO_GET_EXTENSION_FUNCTION_POINTER,		//dwIoControlCode
		&guid,									//lpvInBuffer
		sizeof(guid),							//cbInBuffer
		&pfnEx,									//lpvOutBuffer
		sizeof(pfnEx),							//cbOutBuffer
		&dwBytes,								//lpcbBytesReturned
		NULL,									//lpOverlapped
		NULL									//lpCompletionRoutine
	);
	if (lRet == SOCKET_ERROR)
	{
		std::cout << "WSAIoctl failed, code : " << WSAGetLastError() << endl;
		return NULL;
	}
	return pfnEx;
}

SOCKET MatchServer::GetListenSocket(short shPortNo, int nBacklog)
{
	SOCKET hsoListen = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

	if (hsoListen == INVALID_SOCKET)
	{
		cout << "socket failed, code : " << WSAGetLastError() << endl;
		return INVALID_SOCKET;
	}

	SOCKADDR_IN	sa;
	memset(&sa, 0, sizeof(SOCKADDR_IN));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(shPortNo);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	
	LONG lSockRet = ::bind(hsoListen, (PSOCKADDR)&sa, sizeof(SOCKADDR_IN));
	if (lSockRet == SOCKET_ERROR)
	{
		cout << "bind failed, code : " << WSAGetLastError() << endl;
		closesocket(hsoListen);
		return INVALID_SOCKET;
	}

	lSockRet = listen(hsoListen, nBacklog);
	if (lSockRet == SOCKET_ERROR)
	{
		cout << "listen failed, code : " << WSAGetLastError() << endl;
		closesocket(hsoListen);
		return INVALID_SOCKET;
	}
	return hsoListen;
}

SOCKET MatchServer::GetConnectSocket(char* ip, int port)
{
	SOCKET hSock = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (hSock == INVALID_SOCKET)
	{
		cout << "socket failed, code : " << WSAGetLastError() << endl;
		return hSock;
	}
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);			//Server IP
	addr.sin_port = htons(port);					//Server Port

	for (int i = 0; i < 10; i++)
	{
		if (connect(hSock, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
		{
			cout << "connect failed, code : " << WSAGetLastError() << endl;
			continue;
		}
		return hSock;
	}
	return INVALID_SOCKET;
}

void MatchServer::AcceptEX(SOCKET hsoListen, int count)
{
	LPFN_ACCEPTEX pfnAcceptEx = (LPFN_ACCEPTEX)
		GetSockExtAPI(hsoListen, WSAID_ACCEPTEX);

	for (int i = 0; i < count; i++) 
	{
		SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sock == INVALID_SOCKET)
			return;

		LPPER_IO_DATA ov = new PER_IO_DATA(sock);

		BOOL bIsOK = pfnAcceptEx
		(
			hsoListen,						//sListenSocket
			sock,							//sAcceptSocket
			ov->buffer,						//lpOutputBuffer
			0,								//dwReceiveDataLength
			sizeof(SOCKADDR_IN) + 16,		//dwLocalAddressLength
			sizeof(SOCKADDR_IN) + 16,		//dwRemoteAddressLength
			NULL,							//lpdwBytesReceived
			(LPOVERLAPPED)ov				//lpOverlapped
		);

		if (bIsOK == FALSE)
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				cout << "AcceptEx failed : " << WSAGetLastError() << endl;
				closesocket(ov->hClntSock);
				delete ov;
				break;
			}
		}
	}	
}

unsigned int __stdcall MatchServer::ProcessThread(LPVOID hCompletion)
{
	HANDLE hCompletionPort = hCompletion;

	DWORD bytesTransferred;
	LPPER_IO_DATA perIoData;
	ULONG_PTR	key = 0;
	while (TRUE)
	{
		GetQueuedCompletionStatus(
			hCompletionPort,
			&bytesTransferred,
			&key,
			(LPOVERLAPPED*)&perIoData,
			INFINITE
		);
		mm->ReceivePacket(perIoData);

	}
	return 0;
}