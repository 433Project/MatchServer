#include "MatchServer.h"
#include "AppConfig.h"

void main() {


	AppConfig* config = new AppConfig();
	config->GetAppConfig();

	MatchServer* s = new MatchServer();
	s->RunServer();	
}
