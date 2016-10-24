//#include <iostream>
//#include <winsock2.h>
//#include <MSWSock.h>
//#include <process.h>
//
///*
//#TODO
//- Protocol 맞춰 PER_HANDLE_DATA 변경
//- 하드코딩된 부분 바꾸기(ex ip, port)
//
//#DONE
//- IOCP
//- AcceptEX
//*/
//
//#pragma comment(lib, "Ws2_32.lib")
//using namespace std;
//
//void main(int argc, char* argv[])
//{
//	WSADATA wsd;
//	SOCKET hConnSock;
//	SOCKADDR_IN recvAddr;
//
//	SOCKET hsoListen;
//	int backlog = 10;
//
//	SYSTEM_INFO si;
//	HANDLE hCompletion;
//
//	LPPER_IO_DATA PerIoData;
//	LPPER_HANDLE_DATA PerHandleData;
//	
//	int port = 10000;
//
//	int nErrCode = WSAStartup(MAKEWORD(2, 2), &wsd);
//	if (nErrCode)
//	{
//		cout << "WSAStartup failed, code : " << nErrCode << endl;
//		return;
//	}
//
//	/*if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE));
//	{
//	cout << "SetConsoleCtrlHandler failed, code : " << GetLastError() << endl;
//	return;
//	}
//	*/
//
//	//===================IOCP Creation & Make Thread Pool
//	GetSystemInfo(&si);
//	int numOfCPU = si.dwNumberOfProcessors;
//	int numOfThreads = numOfCPU * 2;
//
//	hCompletion = CreateNewCompletionPort(si.dwNumberOfProcessors);
//
//	for (int i = 0; i < numOfThreads; i++)
//	{
//		_beginthreadex(NULL, 0, ProcessThread, (LPVOID)hCompletion, 0, NULL);
//	}
//
//	//==================Connection to Connection Server
//	hConnSock = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
//	if (hConnSock == INVALID_SOCKET)
//		cout << "socket failed, code : " << WSAGetLastError() << endl;
//laks
//	memset(&recvAddr, 0, sizeof(recvAddr));
//	recvAddr.sin_family = AF_INET;
//	recvAddr.sin_addr.s_addr = inet_addr("10.100.10.10");	//Connection Server IP
//	recvAddr.sin_port = htons(14040);						//Connection Server Port
//
//	if (connect(hConnSock, (SOCKADDR*)&recvAddr, sizeof(recvAddr)) == SOCKET_ERROR)
//		cout << "connect failed, code : "<< WSAGetLastError() << endl;
//
//	AssociateDeviceWithCompletionPort(hCompletion, (HANDLE)hConnSock, hConnSock);
//
//	//=================== Listen Socket for Match Server
//	hsoListen = GetListenSocket(port, backlog);
//
//	AcceptEX(hsoListen);
//
//	while (TRUE)
//	{
//		
//
//	}
//}
