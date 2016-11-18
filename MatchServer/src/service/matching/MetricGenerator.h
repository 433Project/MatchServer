#pragma once
#include "AppConfig.h"
#include "Logger.h"
#include "json.hpp"

// client 능력치 생성
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

	int offenseMax;
	int defenseMax;
	int levelMax;

	int GenerateOffense();
	int GenerateDefense();
	int GenerateLevel();

};