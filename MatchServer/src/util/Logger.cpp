#include "Logger.h"

Logger::Logger()
{
#ifdef _DEBUG
	// dev
	// console logger

	try 
	{
		this->spdLogger = spdlog::stdout_color_mt("console");
	}
	catch (const spdlog::spdlog_ex& ex) 
	{
		cout << "Log setting error" << endl;
	}


#else
	// live
	// file logger

	try
	{
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);

		strftime(buf, sizeof(buf), "%Y-%m-%d_%H_%M_%S", &tstruct);

		string myFile = "D:\\logs\\log";
		myFile.append(string(buf));
		myFile += ".txt";

		//size_t q_size = 4096; //queue size must be power of 2
		//spdlog::set_async_mode(q_size);

		//spdlog::set_level(spdlog::level::info); //Set global log level to info
		this->spdLogger = spdlog::basic_logger_mt("basic_logger", myFile.c_str());
	}
	catch (const spdlog::spdlog_ex& ex)
	{
		cout << "Log setting error" << endl;
	}

#endif // DEBUG
}

Logger::~Logger()
{
	this->spdLogger = NULL;
}

Logger& Logger::GetInstance() 
{
	static Logger instance;

	return instance;
}

/*
void Logger::errFuncName(string funcName, string message) 
{
	string msg =  "[" + funcName + "()] " + message;
	
	this->spdLogger->error(msg);
	this->spdLogger->flush();
}

*/

