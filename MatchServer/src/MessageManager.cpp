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


void MessageManager::ReceivePacket(LPPER_IO_DATA PerIoData)
{
	DWORD flags = MSG_PUSH_IMMEDIATE;
	WSABUF wb;
	wb.buf = PerIoData->buffer, wb.len = sizeof(PerIoData->buffer);
	WSARecv(PerIoData->hClntSock, &wb, 1, NULL, (LPDWORD)&flags, PerIoData, NULL);
}
/*
void MessageManager::ReceiveFlatBuffers(SOCKET s) 
{
	char* buf;
	recv(s, buf, 8, 0);
//	const Packet * p = GetPacket(buf);
//	const Header *h = p->header();
	cout << h->length() << endl;
	cout << h->srcType() << endl;
	cout << h->srcCode() << endl;
	cout << h->dstType() << endl;
	cout << h->dstCode() << endl;
}*/

/*
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

Header* MessageManager::CharPtrToHeader(char* bytes)
{
	Header* head;

	memcpy(&(head->length),bytes, 4);
	memcpy(&(head->srcType), &bytes[4], 4);
	memcpy(&(head->srcCode), &bytes[8], 4);
	memcpy(&(head->dstType), &bytes[12], 4);
	memcpy(&(head->dstCode), &bytes[16], 4);

	return head;
}

char* MessageManager::BodyToCharPtr(Command command, char* data)
{
	int dataLen = sizeof(*data);
	char* body = new char[sizeof(Command)+ dataLen];

	memcpy(body, &(command), 4);
	memcpy(&body[4], &data, dataLen);

	return body;
}
*/