#pragma once
#include "Protocol.h"
#include "Packet_generated.h"

#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

class ProcessConfig
{
public:
	ProcessConfig();
	~ProcessConfig();
	void ProcessConfig::CommandMSID(SOCKET s, Header* h, Body* b);
	void ProcessConfig::CommandMSList(SOCKET s, Header* h, Body* b);
};

