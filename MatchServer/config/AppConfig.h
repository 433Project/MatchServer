#pragma once
#include <string>
using namespace std;

class AppConfig
{

public:
	AppConfig();
	~AppConfig();
	string GetConfig();

private:
	void LoadConfig();
};

