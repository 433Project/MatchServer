#include "MatchServer.h"



MatchServer::MatchServer()
{
}


MatchServer::~MatchServer()
{
}

void MatchServer::RunServer() {

	int nErrCode = WSAStartup(MAKEWORD(2, 2), &wsd);
	if (nErrCode)
	{
		cout << "WSAStartup failed, code : " << nErrCode << endl;
		return;
	}

	/*if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE));
	{
	cout << "SetConsoleCtrlHandler failed, code : " << GetLastError() << endl;
	return;
	}
	*/

	//===================IOCP Creation & Make Thread Pool
	GetSystemInfo(&si);
	int numOfCPU = si.dwNumberOfProcessors;
	int numOfThreads = numOfCPU * 2;

	hCompletion = CreateNewCompletionPort(si.dwNumberOfProcessors);

	for (int i = 0; i < numOfThreads; i++)
	{
		_beginthreadex(NULL, 0, ProcessThread, (LPVOID)hCompletion, 0, NULL);
	}

	//==================Connection to Connection Server
	hConnSock = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (hConnSock == INVALID_SOCKET)
		cout << "socket failed, code : " << WSAGetLastError() << endl;

	memset(&recvAddr, 0, sizeof(recvAddr));
	recvAddr.sin_family = AF_INET;
	recvAddr.sin_addr.s_addr = inet_addr("10.100.10.10");	//Connection Server IP
	recvAddr.sin_port = htons(14040);						//Connection Server Port

	if (connect(hConnSock, (SOCKADDR*)&recvAddr, sizeof(recvAddr)) == SOCKET_ERROR)
		cout << "connect failed, code : " << WSAGetLastError() << endl;

	AssociateDeviceWithCompletionPort(hCompletion, (HANDLE)hConnSock, hConnSock);

	//=================== Listen Socket for Match Server
	hsoListen = GetListenSocket(port, backlog);

	AcceptEX(hsoListen);

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

	LONG lSockRet = bind(hsoListen, (PSOCKADDR)&sa, sizeof(SOCKADDR_IN));
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

void MatchServer::AcceptEX(SOCKET hsoListen)
{
	LPFN_ACCEPTEX pfnAcceptEx = (LPFN_ACCEPTEX)
		GetSockExtAPI(hsoListen, WSAID_ACCEPTEX);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
		return;

	LPPER_IO_DATA ov = new PER_IO_DATA();

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
}

unsigned int __stdcall MatchServer::ProcessThread(LPVOID hCompletion)
{
	HANDLE hCompletionPort = hCompletion;

	DWORD BytesTransferred;
	LPPER_HANDLE_DATA PerHandleData;
	LPPER_IO_DATA PerIoData;

	while (TRUE)
	{
		GetQueuedCompletionStatus(
			hCompletionPort,
			&BytesTransferred,
			reinterpret_cast<PULONG_PTR>(&PerHandleData),
			(LPOVERLAPPED*)&PerIoData,
			INFINITE
		);

		if (BytesTransferred == 0)
		{
			cout << "==> CS disconnected...\n" << endl;
			closesocket(PerHandleData->hClntSock);
			free(PerHandleData);
			free(PerIoData);
			continue;
		}

		PerIoData->wsaBuf.buf[BytesTransferred] = '\0';
		cout << "***CS(" << PerHandleData->clntID << ") sent : " << PerIoData->wsaBuf.buf << "\n" << endl;

		PerIoData->wsaBuf.len = BytesTransferred;
		WSASend(PerHandleData->hClntSock, &(PerIoData->wsaBuf), 1, NULL, 0, NULL, NULL);

		//RECV

	}

	return 0;
}