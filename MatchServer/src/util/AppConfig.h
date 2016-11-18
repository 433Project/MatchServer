#pragma once
#include <string>
#include "json.hpp"
#include <iostream>
#include <fstream>

#include "Logger.h"

using json = nlohmann::json;
using namespace std;

class AppConfig
{
public:
	//---const

	~AppConfig();
	static AppConfig& GetInstance();

	//---logic
	json GetAppConfig();

	template <typename T>
	T GetConfig(string key);
protected:
	AppConfig();

private:
	void LoadConfig();
	//static AppConfig& appConfig;
	json config;
	Logger logger = Logger::GetInstance();
};

