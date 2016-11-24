#pragma once
#include "AppConfig.h"
#include "Matcher.h"

AppConfig::AppConfig()
{
	LoadConfig();
}

AppConfig::~AppConfig() 
{
}

AppConfig& AppConfig::GetInstance() 
{
	static AppConfig instance;

	return instance;
}

void AppConfig::LoadConfig() 
{
	//logger.INFO("HI", "GGG",123);

	ifstream  configFile;
	configFile.open("./config/app.json");

	this->config = json(configFile);
	
	configFile.close();
	cout << "load configuration" << endl;
}



json& AppConfig::GetAppConfig() 
{
	return config;
}
