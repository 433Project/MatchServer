#include "ServerHolder.h"

ServerHolder& ServerHolder::GetInstance() 
{
	static ServerHolder instance;
	return instance;
}

ServerHolder::ServerHolder()
{
}

ServerHolder::~ServerHolder()
{
}

void ServerHolder::AddServer(SERVERID serverId, Server server) 
{
	holder.insert(make_pair(serverId, server));
}

void ServerHolder::DeleteServer(SERVERID serverId) 
{
	holder.erase(serverId);
}

Server ServerHolder::GetServer(SERVERID serverId)
{
	//if(holder.size() != 0)	
		return holder[serverId];	
}
