#pragma once
#include "spdlog\/spdlog.h"
#include <iostream>
#include <time.h>
#include <string>

using namespace std;
using namespace spdlog;

typedef std::shared_ptr<logger> MSLogger;
class FileLogger
{
public:
	FileLogger();
	~FileLogger();
	void info(string message);
	void error(string message);
	
private:
	MSLogger logger;
};

