#pragma once
#include "spdlog\/spdlog.h"
#include <iostream>
#include <time.h>
#include <string>

using namespace std;
using namespace spdlog;

typedef std::shared_ptr<logger> MSLogger;

#define info2(message) info_func_name(__FUNCTION__, message)

class FileLogger
{
public:
	FileLogger();
	~FileLogger();

	//void info(string message);
	void info_func_name(string funcName, string message);
	void error(string message);
	void setPattern(string pattern);
	
	static FileLogger* GetInstance();

private:
	MSLogger logger;
	static FileLogger* fileLogger;
	
};

