#include "Client.h"



Client::Client()
{

}

Client::Client(int clientId, int metric, int serverId, int state, bool attacthed) {
	this->clientId = clientId;
	this->metric = metric;
	this->serverId = serverId;
	this->state = state;
	this->attacthed = attacthed;
}


Client::~Client()
{
}

//=====================================
//====================== getter, setter
int Client::GetMetric() {
	return this->metric;
}

bool Client::SetMetric(int metric) {
	this->metric = metric;
}

CLIENTID Client::GetClientId() {
	return this->clientId;
}
