#pragma once
#include "spdlog\/spdlog.h"
#include <iostream>
#include <time.h>
#include <string>

using namespace std;
using namespace spdlog;

typedef std::shared_ptr<logger> MSLogger;

#ifdef _DEBUG
#define ENV dev
#else
#define ENV live	

#endif
#define INFO(message) infoFuncName(__FUNCTION__,  message)
#define ERROR(message) errFuncName(__FUNCTION__, message)

class Logger
{
public:
	static Logger& GetInstance();
	~Logger();

	void infoFuncName(string funcName, string message);
	void errFuncName(string funcName, string message);
	//void error(string message);
	//void setPattern(string pattern);
	
private:
	MSLogger logger;
	Logger();
};