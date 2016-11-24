#pragma once
#include "spdlog\/spdlog.h"
#include <iostream>
#include <time.h>
#include <string>
#include <type_traits>
#include <Windows.h>
#include <winbase.h>

using namespace std;
using namespace spdlog;

typedef std::shared_ptr<logger> MSLogger;

#ifdef _DEBUG
#define ENV dev
#else
#define ENV live	
#endif

#define Info(...) logInfo(__FUNCTION__, __VA_ARGS__)
#define Error(...) logError(__FUNCTION__, __VA_ARGS__)

class Logger
{
public:
	static Logger& GetInstance();
	~Logger();

	template<class ... Args>
	void logInfo(string funcName, Args ...args);

	template<class ... Args>
	void logError(string funcName, Args ...args);

	template<typename Message>
	string convert(const Message& message);

	template<typename First, typename... Rest>
	string convert(const First& first, const Rest&... rest);

	//void ERROR(string message);

protected:
	Logger();

private:
	MSLogger spdLogger;
};

template<class... Args>
void Logger::logInfo(string funcName, Args ... args)
{
	string convertedMsg = "[" + funcName + "] " + convert(args...);

	this->spdLogger->info(convertedMsg);
	this->spdLogger->flush();
}

template<class... Args>
void Logger::logError(string funcName, Args ... args)
{
	string convertedMsg = "[" + funcName + "] " + convert(args...);

	this->spdLogger->error(convertedMsg);
	this->spdLogger->flush();
}

template<typename Message>
string Logger::convert(const Message& message) 
{
	return int_to_string(message);
}

template<typename First, typename... Rest>
string Logger::convert(const First& first, const Rest&... rest)
{
	string tmp;
	tmp = int_to_string(first);

	return tmp.append(convert(rest...));
}

template<typename T>
string int_to_string(const T& t, std::true_type)
{
	return to_string((int)t);
}

template<typename T>
string int_to_string(const T& t, std::false_type)
{
	return t;
}

template<typename T>
string int_to_string(const T& t)
{
	return int_to_string(t, is_integral<T>());
}