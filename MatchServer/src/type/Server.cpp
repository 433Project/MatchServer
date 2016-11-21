#include "Server.h"

/*
Server* Server::CreateServer() 
{
	Server* server;

	server = new Server();
	return server;
}
*/

Server::Server()
{

}

Server::~Server()
{

}

void Server::CalculateLatency() 
{
	this->latency = difftime(this->endTime, this->startTime);
}

double Server::GetLatency()
{
	return this->latency;
}

void Server::SetStartTime()
{
	//this->startTime = time_t
	time(&this->startTime);
}

void Server::SetEndTime()
{
	time(&this->endTime);
}
