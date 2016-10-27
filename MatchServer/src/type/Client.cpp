#pragma once
#include "Client.h"

Client::Client()
{
	this->clientId = 0;
	this->metric = 0;
	this->serverId = 0;
	this->state = state;
	this->attacthed = attacthed;
}

Client::Client(int clientId, int metric, int serverId, int state, bool attacthed) {
	this->clientId = clientId;
	this->metric = metric;
	this->serverId = serverId;
	this->state = state;
	this->attacthed = attacthed;
}

Client::~Client() {
	delete this;
}

//=====================================
//====================== getter, setter
int Client::GetMetric() {
	return this->metric;
}

bool Client::SetMetric(int metric) {
	this->metric = metric;
	return true;
}

CLIENTID Client::GetClientId() {
	return this->clientId;
}

int Client::GetServerId() {
	return this->serverId;
}
