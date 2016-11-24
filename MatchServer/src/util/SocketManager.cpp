#include "SocketManager.h"
#include "MessageManager.h"
#include <iostream>
#include <map>
#include <winsock2.h>
#include <mswsock.h>
#pragma comment(lib, "Ws2_32.lib")

SocketManager* SocketManager::instance = nullptr;
SocketManager::SocketManager()
{
	iocpM = IOCPManager::GetInstance();
	msgM = new MessageManager();

}

SocketManager::~SocketManager()
{
	if (listenSock != INVALID_SOCKET)
		closesocket(listenSock);
	if (cfSocket != INVALID_SOCKET)
		closesocket(listenSock);
	if (csSocket != INVALID_SOCKET)
		closesocket(listenSock);

	std::unordered_map<int, SOCKET>::iterator iter;
	for (iter = msList.begin(); iter != msList.end(); iter++) 
	{
		closesocket(iter->first);
	}
}

SocketManager* SocketManager::GetInstance()
{
	if (instance == nullptr)
		instance = new SocketManager();
	return instance;
}

bool SocketManager::CreateListenSocket()
{
	listenSock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

	if (listenSock == INVALID_SOCKET)
	{
		logger.Error("socket failed, code : ", WSAGetLastError());
		return false;
	}

	if (config.Contains("Listen"))
		port = config.GetConfig<json>("Listen")["port"];

	logger.Info("Listen Socket(", listenSock, ") port : ", port);

	SOCKADDR_IN	sa;
	memset(&sa, 0, sizeof(SOCKADDR_IN));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	LONG lSockRet = ::bind(listenSock, (PSOCKADDR)&sa, sizeof(SOCKADDR_IN));
	if (lSockRet == SOCKET_ERROR)
	{
		logger.Error("bind failed, code : " , WSAGetLastError());
		closesocket(listenSock);
		return false;
	}
	lSockRet = listen(listenSock, backlog);
	if (lSockRet == SOCKET_ERROR)
	{
		logger.Error("listen  failed, code : " , WSAGetLastError());
		closesocket(listenSock);
		return false;
	}

	if (!iocpM->AssociateDeviceWithCompletionPort((HANDLE)listenSock, LISTEN))
	{
		logger.Error("Associate listen socket with completion port  failed");
	}
	return true;
}

bool SocketManager::CreateSocket(COMPLETIONKEY type, string ip, int port, int id)
{
	SOCKET sock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	if (sock == INVALID_SOCKET)
	{
		logger.Error(EnumNamesCOMPLETIONKEY()[type], "socket failed, code : ", WSAGetLastError());
		return false;
	}
	logger.Info(EnumNamesCOMPLETIONKEY()[type]," Socket(", sock, ")");
	
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip.c_str());	//Server IP
	addr.sin_port = htons(port);					//Server Port
	
	if (connect(sock, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		logger.Error(EnumNamesCOMPLETIONKEY()[type]," connect failed, code : ",  WSAGetLastError());
		return false;
	}

	if (type == CONNECTION)
	{
		csSocket = sock;
	}
	else if (type == CONFIG)
	{
		cfSocket = sock;
	}
	else if (type == MATCHING)
	{
		msList.insert(pair<int, SOCKET>(id, sock));
	}
	
	//IOCP 등록
	if (!iocpM->AssociateDeviceWithCompletionPort((HANDLE)sock, type))
		logger.Error("Associate ", EnumNamesCOMPLETIONKEY()[type], " socket with completion port fail");

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

		DWORD dwBytes;
		IO_DATA* ov = new IO_DATA(sock);
		ov->buffer = new char[(sizeof(SOCKADDR_IN) + 16)*2 + sizeof(Header)];
		BOOL bIsOK = pfnAcceptEx
		(
			listenSock,						//sListenSocket
			sock,							//sAcceptSocket
			ov->buffer,						//lpOutputBuffer
			sizeof(Header),					//dwReceiveDataLength
			sizeof(SOCKADDR_IN) + 16,		//dwLocalAddressLength
			sizeof(SOCKADDR_IN) + 16,		//dwRemoteAddressLength
			&dwBytes,						//lpdwBytesReceived
			(LPOVERLAPPED)ov				//lpOverlapped
		);

		if (bIsOK == FALSE)
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				logger.Error("AcceptEx failed : ", WSAGetLastError());
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
		logger.Error("WSAIoctl failed, code : ", WSAGetLastError());
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
	DWORD flag = MSG_PUSH_IMMEDIATE;
	WSABUF wsaBuf;
	wsaBuf.buf = ioData->buffer;
	wsaBuf.len = packetSize;
	WSARecv(ioData->hClntSock, &wsaBuf, 1, NULL, &flag, ioData, NULL);
}

void SocketManager::AcceptMS(SOCKET sock, int id)
{
	iocpM->AssociateDeviceWithCompletionPort((HANDLE)sock, MATCHING);
	logger.Info("New Matching Server(", sock, "), id = ", id);
	msList.insert(pair<int, SOCKET>(id, sock));
	AcceptEX(1);
}

void SocketManager::CloseSocketMS(int id)
{
	logger.Info("Closed Matching Socket(", msList[id], "), id = ", id);
	closesocket(msList[id]);
	msList.erase(id);
}


void SocketManager::HeartBeats()
{
	while (true)
	{
		for each (pair<int, SOCKET> kvp in msList)
		{
			std::unordered_map<int, int>::const_iterator got = heartbeats.find(kvp.first);

			if (got == heartbeats.end())
			{
				heartbeats.insert(pair<int, int>(kvp.first, 0));
			}

			if (++heartbeats[kvp.first]>3)
			{
				CloseSocketMS(kvp.first);
			}
			else
			{
				char* data = new char[packetSize];
				msgM->MakePacket(data, MATCHING_SERVER, kvp.first, COMMAND_HEALTH_CHECK_REQUEST, STATUS_NONE, "", "", serverID);
				SendPacket(msList[kvp.first], data);
				if (data != nullptr)
					delete data;
				//서버의 보낸 시간을 저장하자
			}
		}

	}

}