#pragma once
#include "MetricGenerator.h"
#include <cstdlib>


MetricGenerator::MetricGenerator() {

}

MetricGenerator::~MetricGenerator() {

}


int MetricGenerator::GenerateLevel() {
	return rand() % 100;
}

int MetricGenerator::GenerateOffense() {
	return rand() % 100;
}

int MetricGenerator::GenerateDefense() {
	return rand() % 100;// 0 ~ 99
}

int MetricGenerator::GenerateMetric() {

	int level = GenerateLevel();
	int offense = GenerateOffense();
	int defense = GenerateDefense();

	return level * levelWeight + offense* offsenseWeight + defense*defenseWeight;
}