
#pragma once
#include "Protocol.h"
#include "ClientHolder.h"
#include "MetricGenerator.h"

class CommandMatchRequest 
{

private:
	ClientHolder clientHolder = ClientHolder::GetInstance();
	MetricGenerator* metricGenerator = new MetricGenerator();

public:

	// handle Matching Request
	void HandleCommand(Packet packet) 
	{

		int metric = metricGenerator->GenerateMetric();

		clientHolder.AddClient(metric, Client(packet.header->srcCode,metric, 0, ClientState::Waiting, true));
	}

};