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


void MessageManager::ReceivePacket(IO_DATA* ioData)
{
	ioData->buffer = new char[packetSize];

	DWORD flags = MSG_PUSH_IMMEDIATE;
	WSABUF wb;
	wb.buf = ioData->buffer;
	wb.len = packetSize;
	WSARecv(ioData->hClntSock, &wb, 1, NULL, &flags, ioData, NULL);
}

char* MessageManager::MakePacket(SrcDstType dstType, int dstCode, Command comm, Status st, string data1, string data2)
{
	flatbuffers::FlatBufferBuilder builder;
	flatbuffers::Offset<Body> body;
	
	if(data1.empty() && data2.empty())
		body = CreateBody(builder, comm, st);
	else if (data2.empty())
		body = CreateBody(builder, comm, st, builder.CreateString(data1));
	else
		body = CreateBody(builder, comm, st, builder.CreateString(data1), builder.CreateString(data1));

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
	uint8_t* d = new uint8_t[len];
	memset(d, 0, len);
	memcpy(d, &data[sizeof(Header)], len);
	auto b = GetBody(d);
	return b;
}
