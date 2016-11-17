#include "MatchServer.h"
#include "FileLogger.h"

void main() {
	
	FileLogger* logger = FileLogger::GetInstance();
	logger->LogInfo("info test");
	//logger->error("error test");

	MatchServer* s = new MatchServer();
	s->RunServer();	
}
