#pragma once
#include <unordered_map>
#include "Server.h"

using namespace std;

// handle matching servers 
class ServerHolder
{
public:	
	~ServerHolder();

	static ServerHolder& GetInstance();

	void AddServer(SERVERID serverId, Server server);
	void DeleteServer(SERVERID serverId);
	Server GetServer(SERVERID serverId);

private:
	ServerHolder();
	unordered_map<SERVERID, Server> holder;
};

