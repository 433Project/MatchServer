#pragma once
#include "spdlog\/spdlog.h"
#include <iostream>
#include <time.h>
#include <string>

using namespace std;
using namespace spdlog;

typedef std::shared_ptr<logger> MSLogger;

#define LogInfo(message) infoFuncName(__FUNCTION__,  message)
#define LogError(message) errFuncName(__FUNCTION__, message)

inline std::string className(const std::string& prettyFunction)
{
	size_t colons = prettyFunction.find("::");
	if (colons == std::string::npos)
		return "::";
	size_t begin = prettyFunction.substr(0, colons).rfind(" ") + 1;
	size_t end = colons - begin;

	return prettyFunction.substr(begin, end);
}

class FileLogger
{
public:
	FileLogger();
	~FileLogger();


	void infoFuncName(string funcName, string message);
	void errFuncName(string funcName, string message);
	//void error(string message);
	void setPattern(string pattern);
	
	static FileLogger* GetInstance();

private:
	MSLogger logger;
	static FileLogger* fileLogger;
};

