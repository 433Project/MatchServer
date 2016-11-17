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
	AppConfig();
	~AppConfig();
	static AppConfig* GetInstance();

	//---logic
	json GetAppConfig();

	/*
	string GetConfig(string key);
	json GetConfig(string key);
	*/

	template <typename T>
	T GetConfig(string key);

	Logger logger = Logger::GetInstance();

private:
	void LoadConfig();
	static AppConfig* appConfig;
	json config;
	
};

