#pragma once
#include "ClientHolder.h"
#include "MetricGenerator.h"


// client matching ผ๖วเ
class Matcher {


private :
	Matcher();
	~Matcher();

	static Matcher* instance;
	static ClientHolder* clientHolder;
	MetricGenerator metricGenerator;

public:
	static Matcher* GetInstance();
	void Matching(Client client);

	int FindOpposite(Client client);
};


