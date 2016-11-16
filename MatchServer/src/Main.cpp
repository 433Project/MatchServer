#include "MatchServer.h"
#include "FileLogger.h"

void main() {
	
	FileLogger logger = FileLogger();
	logger.info("info test");
	logger.error("error test");

	MatchServer* s = new MatchServer();
	s->RunServer();	
}
