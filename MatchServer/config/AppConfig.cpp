#include "AppConfig.h"
#include <iostream>
#include <fstream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

AppConfig::AppConfig() {
	LoadConfig();
}

AppConfig::~AppConfig() {

}

void AppConfig::LoadConfig() {
	ifstream  confFile;
	confFile.open("app.json");
}


string AppConfig::GetConfig() {
	return "";
}