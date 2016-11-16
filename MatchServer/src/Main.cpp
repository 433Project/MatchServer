#include "MatchServer.h"
#include "FileLogger.h"

void main() {
	
	FileLogger logger = FileLogger();
	logger.info("test");
	
	/*
	MatchServer* s = new MatchServer();
	s->RunServer();	
	*/

	while (true) {}
	
}
