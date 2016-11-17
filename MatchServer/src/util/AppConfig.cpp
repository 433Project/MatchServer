#pragma once
#include "AppConfig.h"
#include "ConsoleLogger.h"

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
	ConsoleLogger::PrintMessage("load . . .");

	ifstream  configFile;
	configFile.open("./config/app.json");

	json j(configFile);

	configFile.close();
}

json AppConfig::GetAppConfig() {
	return "";
}

string AppConfig::GetConfig(string key) {
	return "";
}