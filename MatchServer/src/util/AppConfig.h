#pragma once
#include <string>
#include "json.hpp"

#include <iostream>
#include <fstream>

using json = nlohmann::json;
using namespace std;

class AppConfig
{
public:
	//---const
	AppConfig();
	~AppConfig();
	static AppConfig* GetInstance();

	//---logic
	json GetAppConfig();
	string GetConfig(string key);
	
private:
	void LoadConfig();
	static AppConfig* appConfig;
};

