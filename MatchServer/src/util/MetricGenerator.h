#pragma once
#include <iostream>
#include <process.h>

using namespace std;


class MetricGenerator {

public:
	MetricGenerator();
	~MetricGenerator();
	int GenerateMetric();

private:
	int offense;
	int defense;
	int level;

	int offsenseWeight;
	int defenseWeight;
	int levelWeight;

	int GenerateOffense();
	int GenerateDefense();
	int GenerateLevel();

};