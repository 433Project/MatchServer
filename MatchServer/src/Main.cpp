#include "MatchServer.h"
#include "FileLogger.h"

void main() {
	MatchServer* s = new MatchServer();
	s->RunServer();	
}
