#include "MessageManager.h"


MessageManager::MessageManager()
{

}


MessageManager::~MessageManager()
{
}

DWORD MessageManager::SendPacket(SOCKET s, char* data)
{
	WSABUF wsabuf;
	wsabuf.buf = data;
	wsabuf.len = packetSize;

	DWORD bytesSent;
	WSASend(s, &wsabuf, 1, &bytesSent, 0, NULL, NULL);
	return bytesSent;
}


void MessageManager::ReceivePacket(LPPER_IO_DATA PerIoData)
{
	DWORD flags = MSG_PUSH_IMMEDIATE;
	WSABUF wb;
	wb.buf = PerIoData->buffer, wb.len = sizeof(PerIoData->buffer);
	WSARecv(PerIoData->hClntSock, &wb, 1, NULL, &flags, PerIoData, NULL);
}

char* MessageManager::MakePacket(SrcDstType dstType, int dstCode, Command comm, Status st, string data)
{
	flatbuffers::FlatBufferBuilder builder;
	flatbuffers::Offset<Body> body = CreateBody(builder, comm, st, builder.CreateString(data));
	builder.Finish(body);

	uint8_t* buf = builder.GetBufferPointer();
	char* b = reinterpret_cast<char*>(buf);
	int len = builder.GetSize();

	Header* h = new Header(len, MATCHING_SERVER, 0, dstType, dstCode);

	char* bytes = new char[packetSize];
	memset(bytes, 0, packetSize);
	memcpy(bytes, h, sizeof(Header));
	memcpy(&bytes[sizeof(Header)], b, len);

	delete h;

	return bytes;
}

Header* MessageManager::ReadHeader(char* data)
{
	Header* h = new Header();
	memcpy(h, data, sizeof(Header));

	return h;
}

const Body* MessageManager::ReadBody(int len, char* data)
{
	char* d = new char[len];
	memset(d, 0, len);
	memcpy(d, &data[sizeof(Header)], len);
	const Body* b = GetBody(d);
	return b;
}
