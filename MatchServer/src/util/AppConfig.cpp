#pragma once
#include "AppConfig.h"

AppConfig::AppConfig() 
{
	LoadConfig();
}

AppConfig::~AppConfig() 
{
	
}

//AppConfig* AppConfig::appConfig = nullptr;
AppConfig& AppConfig::GetInstance() 
{
	static AppConfig instance;

	return instance;
}

void AppConfig::LoadConfig() 
{
	ifstream  configFile;
	configFile.open("./config/app.json");

	this->config = json(configFile);

	configFile.close();
	logger.INFO("Server Configuration load");
}

json AppConfig::GetAppConfig() 
{
	return config;
}

template<typename T>
T AppConfig::GetConfig(string key) 
{
	return config[key];
}

