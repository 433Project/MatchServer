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

void ServerHolder::AddServer(Server server) 
{

}


void ServerHolder::DeleteServer(SERVERID serverId) 
{
	
}

Server ServerHolder::GetServer(SERVERID serverId)
{
	//if(holder.size() != 0)	
		return holder[serverId];
	
}
