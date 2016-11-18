#pragma once
#include "AppConfig.h"

//Logger AppConfig::logger = Logger::GetInstance();

AppConfig::AppConfig() {
	LoadConfig();
}

AppConfig::~AppConfig() {
	
}

AppConfig* AppConfig::appConfig = nullptr;
AppConfig* AppConfig::GetInstance() {

	if (appConfig == nullptr) {
		appConfig = new AppConfig();
	}
	return appConfig;
}

void AppConfig::LoadConfig() {
	ifstream  configFile;
	configFile.open("./config/app.json");

	this->config = json(configFile);

	configFile.close();
}

json AppConfig::GetAppConfig() {
	return config;
}

template<typename T>
T AppConfig::GetConfig(string key) {
	return config[key];
}

