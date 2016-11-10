#pragma once
#include "ClientHolder.h"
#include "MetricGenerator.h"
#include "CommandHandler.h"



// client matching ผ๖วเ
class Matcher {

private:
	Matcher();
	~Matcher();
	static Matcher* instance;

	//ClientHolder* clientHolder;

	MetricGenerator* metricGenerator;
	CommandHandler* commandHandler;
	
	ClientHolder* clientHolder;

public:

	static Matcher* GetInstance();

	void MainLogic();

	void Matching();
	//void Matching(Client client);
	void HandleMessage();

	// find opposite client id 
	int FindOpposite(Client client);
};


