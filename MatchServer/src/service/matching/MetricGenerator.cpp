#pragma once
#include "MetricGenerator.h"
#include <cstdlib>

MetricGenerator::MetricGenerator() 
{
	AppConfig appConfig = AppConfig::GetInstance();

	cout << appConfig.GetAppConfig() << endl;

	//json weights = appConfig.GetConfig<json>("weight");
	appConfig.GetConfig<string>("max");

	//this->levelWeight = weights["level"];
	//this->defenseWeight = weights["defense"];
	//this->offsenseWeight = weights["offense"]; 

	//this->levelMax = max["level"];
	//this->defenseMax= max["defense"];
	//this->offenseMax= max["offense"];

	//if(appConfig)
	//	delete appConfig;
}

MetricGenerator::~MetricGenerator() 
{

}

int MetricGenerator::GenerateLevel() 
{
	return rand() % this->levelMax;
}


int MetricGenerator::GenerateDefense() 
{
	return rand() % this->defenseMax;// 0 ~ 99
}

int MetricGenerator::GenerateOffense() 
{
	return rand() % this->offenseMax;
}

int MetricGenerator::GenerateMetric() 
{

	int level = GenerateLevel();
	int offense = GenerateOffense();
	int defense = GenerateDefense();

	return level * levelWeight + offense* offsenseWeight + defense*defenseWeight;
}