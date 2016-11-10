#pragma once

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

	int GenerateOffense();
	int GenerateDefense();
	int GenerateLevel();

};