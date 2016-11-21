#pragma once
#include <ctime>

typedef int SERVERID;

// 
class Server
{
public:
	Server();
	~Server();
	
	void SetStartTime();
	void SetEndTime();

	double GetLatency();
	void CalculateLatency();

private:
	double latency;

	time_t startTime;
	time_t endTime;

	SERVERID serverId;	
};

