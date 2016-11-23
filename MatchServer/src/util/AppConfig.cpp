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

//true : exist, false : none 
bool AppConfig::Contains(string key) 
{

	if (this->config.find(key) != this->config.end()) 
	{
		return true;
	}

	return false;
}

json& AppConfig::GetAppConfig() 
{
	return config;
}
