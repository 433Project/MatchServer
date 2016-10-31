#include "MessageManager.h"

MessageManager::MessageManager()
{

}


MessageManager::~MessageManager()
{
}

void MessageManager::SendPacket(SOCKET socket, char* buf)
{
	//WSASend(socket, &(ov->wsaBuf), 1, NULL, 0, NULL, NULL);
	send(socket, buf, strlen(buf), 0);
}

/*
void MessageManager::ReceivePacket(SOCKET socket, LPPER_IO_DATA ov)
{
	WSARecv(socket, &(ov->wsaBuf), 1, NULL, 0, ov, NULL);
}
*/

char* MessageManager::HeaderToCharPtr(Header *h)
{
	char* head = new char[20];

	memcpy(head, &(h->length), 4);
	memcpy(head+4, &(h->srcType), 4);
	memcpy(head+8, &(h->srcCode), 4);
	memcpy(head+12, &(h->dstType), 4);
	memcpy(head+16, &(h->dstCode), 4);

	return head;
}
