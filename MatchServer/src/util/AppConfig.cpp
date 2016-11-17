#include "AppConfig.h"
#include "ConsoleLogger.h"

AppConfig::AppConfig() {
	LoadConfig();
}

AppConfig::~AppConfig() {
	
}

void AppConfig::LoadConfig() {
	ConsoleLogger::PrintMessage("load . . .");

	ifstream  configFile;
	configFile.open("./config/app.json");

	json j(configFile);

	configFile.close();
}

string AppConfig::GetAppConfig() {
	return "";
}
