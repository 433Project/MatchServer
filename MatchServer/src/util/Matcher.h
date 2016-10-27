#pragma once
#include "ClientHolder.h"
#include "MetricGenerator.h"

// client matching ����
class Matcher {

private:
	Matcher();
	~Matcher();
	static Matcher* instance;

	ClientHolder* clientHolder;

	MetricGenerator* metricGenerator;

public:
	static Matcher* GetInstance();

	void Matching(Client client);
	int FindOpposite(Client client);
};


