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
/*
flatbuffers::Offset<Header> MessageManager::MakeHeader(int len, SrcDstType srcType, int srcCode, SrcDstType dstType, int dstCode)
{

	flatbuffers::FlatBufferBuilder builder(1024);
	return CreateHeader(builder, len, srcType, srcCode, dstType, dstCode);
}

flatbuffers::Offset<Body> MakeBody(Command com, string data)
{
	flatbuffers::FlatBufferBuilder builder(1024);

	return CreateBody(builder, com, builder.CreateString(data));
}

flatbuffers::Offset<Packet> MessageManager::MakePacket(flatbuffers::Offset<Header> h, flatbuffers::Offset<Body> b)
{
	flatbuffers::FlatBufferBuilder builder(1024);
	return CreatePacket(builder, h, b);
}*/

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
