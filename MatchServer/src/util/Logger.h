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

#define ERROR(messages) errFuncName(__FUNCTION__, messages)

class Logger
{
public:
	static Logger& GetInstance();
	~Logger();

	template<typename ...Messages>
	void infoFuncName(string funcName, Messages&... messages);

	template<typename TF>
	void infoFuncName(string funcName,TF const& f);

	template<class ... Args>
	void INFO(Args ...args);

	void errFuncName(string funcName, string message);


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
void Logger::INFO(Args ... args)
{
	string message;
	
	std::vector<string> vec = {args ...};

	for (int idx = 0; idx < vec.size(); idx++) 
	{
		message += vec[idx];
	}

	this->spdLogger->info(message);
	this->spdLogger->flush();
}

template<typename Message>
string Logger::convert(const Message& message) 
{
	if (typeid(first).name() == typeid(int).name()) {
		return to_string(message);
	}
	return message;
}

template<typename First, typename... Rest>
string Logger::convert(const First& first, const Rest&... rest)
{
	string tmp;
	/*
	if (typeid(first).name() == typeid(int).name()) {
		tmp = to_string(first);
		tmp.append(convert(rest... ));
	}
	*/
	
	return ((string)to_string(first)).append(convert(rest...));
}
