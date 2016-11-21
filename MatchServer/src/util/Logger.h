#pragma once
#include "spdlog\/spdlog.h"
#include <iostream>
#include <time.h>
#include <string>
#include <type_traits>

using namespace std;
using namespace spdlog;

typedef std::shared_ptr<logger> MSLogger;

#ifdef _DEBUG
#define ENV dev
#else
#define ENV live	
#endif

//#define Error(messages) errFuncName(__FUNCTION__, messages)

class Logger
{
public:
	static Logger& GetInstance();
	~Logger();

	template<class ... Args>
	void Info(Args ...args);

	template<class ... Args>
	void Error(Args ...args);

	//void errFuncName(string funcName, string message);

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
void Logger::Info(Args ... args)
{
	string convertedMsg = convert(args...);

	this->spdLogger->info(convertedMsg);
	this->spdLogger->flush();
}

template<class... Args>
void Logger::Error(Args ... args)
{
	string convertedMsg = convert(args...);

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