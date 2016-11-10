#pragma once
#include <string>

using namespace std;

class AppConfig
{

public:
	AppConfig();
	~AppConfig();
	string GetAppConfig();

private:
	void LoadConfig();
};

