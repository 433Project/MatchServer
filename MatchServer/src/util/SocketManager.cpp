#include "SocketManager.h"
#include "Logger.h"


Logger& logs = Logger::GetInstance();

SocketManager* SocketManager::instance = 0;
IOCPManager* iocp = IOCPManager::GetInstance();

SocketManager::SocketManager()
{
	
}

SocketManager::~SocketManager()
{
	if (listenSock != INVALID_SOCKET)
		closesocket(listenSock);
	if (cfSocket != INVALID_SOCKET)
		closesocket(listenSock);
	if (csSocket != INVALID_SOCKET)
		closesocket(listenSock);

	map<SOCKET, int>::iterator iter;
	for (iter = msList.begin(); iter != msList.end(); iter++) 
	{
		closesocket(iter->first);
	}
}

SocketManager* SocketManager::GetInstance()
{
	if (instance == 0)
		instance = new SocketManager();
	return instance;
}

bool SocketManager::CreateListenSocket()
{
	listenSock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

	if (listenSock == INVALID_SOCKET)
	{
		logs.ERROR("socket failed, code : " + WSAGetLastError());
		return false;;
	}

	SOCKADDR_IN	sa;
	memset(&sa, 0, sizeof(SOCKADDR_IN));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	LONG lSockRet = ::bind(listenSock, (PSOCKADDR)&sa, sizeof(SOCKADDR_IN));
	if (lSockRet == SOCKET_ERROR)
	{
		logs.ERROR("bind failed, code : " + WSAGetLastError());
		closesocket(listenSock);
		return false;
	}
	logs.INFO("bind()");
	lSockRet = listen(listenSock, backlog);
	if (lSockRet == SOCKET_ERROR)
	{
		logs.ERROR("listen  failed, code : " + WSAGetLastError());
		closesocket(listenSock);
		return false;
	}

	logs.INFO("Listen()");

	if (iocp->AssociateDeviceWithCompletionPort((HANDLE)listenSock, LISTEN))
	{
		logs.INFO("Associate listen socket with completion port");
	}
	else 
	{
		logs.ERROR("Associate listen socket with completion port  failed");
	}
	return true;
}

bool SocketManager::CreateSocket(int type, char* ip, int id)
{
	SOCKET sock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	int port = 0;
	
	if (type == CONNECTION)
	{
		csSocket = sock;
		port = csPort;
	}
	else if (type == CONFIG)
	{
		cfSocket = sock;
		port = cfPort;
	}
	else if (type == MATCHING)
	{
		msList.insert(pair<SOCKET, int>(sock, id));
		port = this->port;
	}

	if (sock == INVALID_SOCKET)
	{
		logs.ERROR("socket failed, code : " + WSAGetLastError());
		return false;
	}

	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);			//Server IP
	addr.sin_port = htons(port);					//Server Port
	
	if (connect(sock, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		logs.ERROR("connect failed, code : " + WSAGetLastError());
		return false;
	}

	//IOCP µî·Ï
	iocp->AssociateDeviceWithCompletionPort((HANDLE)sock, MATCHING);
	
	//initial receive
	IO_DATA* ioData = new IO_DATA(sock);
	ReceivePacket(sock, ioData);

	return true;
}

void SocketManager::AcceptEX(int count)
{
	LPFN_ACCEPTEX pfnAcceptEx = (LPFN_ACCEPTEX)
		GetSockExtAPI(WSAID_ACCEPTEX);

	for (int i = 0; i < count; i++)
	{
		SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sock == INVALID_SOCKET)
			return;

		IO_DATA* ov = new IO_DATA(sock);
		ov->buffer = new char[512];
		BOOL bIsOK = pfnAcceptEx
		(
			listenSock,						//sListenSocket
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

PVOID SocketManager::GetSockExtAPI(GUID guidFn)
{
	PVOID pfnEx = NULL;
	GUID guid = guidFn;
	DWORD dwBytes = 0;

	LONG lRet = ::WSAIoctl
	(
		listenSock,									//Socket
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


DWORD SocketManager::SendPacket(SOCKET socket, char* data)
{
	WSABUF wsabuf;
	wsabuf.buf = data;
	wsabuf.len = packetSize;

	DWORD bytesSent;
	WSASend(socket, &wsabuf, 1, &bytesSent, 0, NULL, NULL);
	return bytesSent;
}


void SocketManager::ReceivePacket(SOCKET socket, IO_DATA* ioData)
{
	ioData->buffer = new char[packetSize];

	DWORD flags = MSG_PUSH_IMMEDIATE;
	WSABUF wb;
	wb.buf = ioData->buffer;
	wb.len = packetSize;
	WSARecv(ioData->hClntSock, &wb, 1, NULL, &flags, ioData, NULL);
}