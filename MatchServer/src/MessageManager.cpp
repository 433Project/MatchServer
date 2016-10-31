#include "MessageManager.h"

MessageManager::MessageManager()
{

}


MessageManager::~MessageManager()
{
}

void MessageManager::SendPacket(SOCKET socket, char* buf, int len)
{
	//WSASend(socket, &(ov->wsaBuf), 1, NULL, 0, NULL, NULL);
	send(socket, buf, len, 0);
}


void MessageManager::ReceivePacket(LPPER_HANDLE_DATA PerHandleData)
{
	LPPER_IO_DATA PerIoData = (LPPER_IO_DATA)malloc(sizeof(PER_IO_DATA));
	memset(PerIoData, 0, sizeof(OVERLAPPED));
	PerIoData->wsaBuf.len = 1024;
	PerIoData->wsaBuf.buf = PerIoData->buffer;

	DWORD flags = 0;
	WSARecv(PerHandleData->hClntSock, &(PerIoData->wsaBuf), 1, NULL, (LPDWORD)&flags, PerIoData, NULL);
}


char* MessageManager::HeaderToCharPtr(Header *h)
{
	char* head = new char[20];

	memcpy(head, &(h->length), 4);
	memcpy(&head[4], &(h->srcType), 4);
	memcpy(&head[8], &(h->srcCode), 4);
	memcpy(&head[12], &(h->dstType), 4);
	memcpy(&head[16], &(h->dstCode), 4);
	
	return head;
}
