#pragma once

typedef int SERVERID;

class Server
{
public:
	Server();
	~Server();
	//static Server* CreateServer();

	double GetLatency();
	
private:


	double latency;
	SERVERID serverId;
	
};

