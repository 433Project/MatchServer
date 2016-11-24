#include "MessageManager.h"

MessageManager::MessageManager()
{

}


MessageManager::~MessageManager()
{
}


void MessageManager::MakePacket(char* bytes, TERMINALTYPE dstType, int dstCode, COMMAND comm, STATUS st, string data1, string data2, int srcCode)
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

	Header* h = new Header(len, MATCHING_SERVER, srcCode, dstType, dstCode);

	memcpy(bytes, h, sizeof(Header));
	memcpy(&bytes[sizeof(Header)], b, len);

	delete h;
}

void MessageManager::ReadPacket(Packet* p, char* data)
{
	memcpy(p->header, data, sizeof(Header));

	uint8_t* d = new uint8_t[p->header->length];
	memset(d, 0, p->header->length);
	memcpy(d, &data[sizeof(Header)], p->header->length);
	p->body = (Body*)GetBody(d);
}

void MessageManager::HeaderToBytes(char* bytes, TERMINALTYPE dstType, int dstCode, int srcCode)
{
	Header* h = new Header(0, MATCHING_SERVER, srcCode, dstType, dstCode);
	memcpy(bytes, h, sizeof(Header));
}

void MessageManager::BytesToHeader(char* bytes, Header* h)
{
	memcpy(h, bytes, sizeof(Header));
}

void MessageManager::split(const string& s, char del, vector<string>& v) 
{
	string::size_type i = 0;
	string::size_type j = s.find(del);

	while (j != string::npos) {
		v.push_back(s.substr(i, j - i));
		i = ++j;
		j = s.find(del, j);

		if (j == string::npos)
			v.push_back(s.substr(i, s.length()));
	}
}