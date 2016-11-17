#pragma once
#include "MetricGenerator.h"
#include <cstdlib>

MetricGenerator::MetricGenerator() {
	
	//
	//AppConfig* appConfig = AppConfig::GetInstance();
	//json weights = appConfig->GetConfig<json>("as");

	//this->levelWeight = weights["level"];
	//this->defenseWeight = weights["defense"];
	//this->offsenseWeight = weights["offense"]; 
	//
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