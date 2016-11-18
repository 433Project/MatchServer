#include "Logger.h"

Logger::Logger()
{
#ifdef _DEBUG
	// dev
	// console logger
	try 
	{
		this->logger = spdlog::stdout_color_mt("console");
	}
	catch (const spdlog::spdlog_ex& ex) 
	{
		cout << "Log setting error" << endl;
	}
#else
	// live
	// file logger

	string fileName = "";
	string path = "logs/";
	string extension = ".txt";

	try 
	{
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);

		strftime(buf, sizeof(buf), "%Y-%m-%d_%H_%M_%S", &tstruct);

		fileName += path;
		fileName.append(string(buf));
		fileName += extension;

		size_t q_size = 4096; //queue size must be power of 2
		spdlog::set_async_mode(q_size);

		spdlog::set_level(spdlog::level::info); //Set global log level to info
		this->logger = spdlog::basic_logger_mt("ms_file_logger", fileName);
	}
	catch (const spdlog::spdlog_ex& ex) 
	{
		cout << "Log setting error" << endl;
	}
#endif // DEBUG
}

Logger::~Logger()
{
	this->logger = NULL;
}

Logger& Logger::GetInstance() 
{
	static Logger instance;

	return instance;
}

void Logger::infoFuncName(string funcName, string message) 
{
	string msg = "[" + funcName + "()] " + message;

	this->logger->info(msg);
	this->logger->flush();
}

void Logger::errFuncName(string funcName, string message) 
{
	string msg =  "[" + funcName + "()] " + message;

	this->logger->error(msg);
	this->logger->flush();
}

