#pragma once
#include "ClientHolder.h"
#include "MetricGenerator.h"
#include "MessageQueue.h"

// client matching ผ๖วเ
class Matcher {

private:
	Matcher();
	~Matcher();
	static Matcher* instance;

	ClientHolder* clientHolder;

	MetricGenerator* metricGenerator;
	MessageQueue* messageQueue;

public:
	static Matcher* GetInstance();

	void Process();
	void Matching();
	void HandleMessageQueue();


	int FindOpposite(Client client);

};


