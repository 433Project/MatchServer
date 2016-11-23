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
	json& GetAppConfig();

	template <typename T>
	T GetConfig(string key);

	bool Contains(string key);

private:
	void LoadConfig();
	AppConfig();

	json config;
	Logger& logger = Logger::GetInstance();
};

template<typename T>
T AppConfig::GetConfig(string key)
{
	
	return config[key];
}