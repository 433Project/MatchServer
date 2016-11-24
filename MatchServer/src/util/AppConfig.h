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
	
	template <typename ...Keys>
	bool Contains(Keys&... keys);

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

//true : exist, false : none 
template<typename... Keys>
bool AppConfig::Contains(Keys&... keys)
{
	vector<string> vec = { keys ... };
	auto target = this->config;

	if (0 != vec.size())
	{
		// 입력받은 key 배열에 대해서 하나씩 leveling
		for (auto key = vec.begin(); key != vec.end(); ++key)
		{
			if (target.find(*key) == target.end())
			{
				return false;
			}

			//target = *(target.find(key));
			target = target[*key];
		}

		return true;
	}
	return false;
}
