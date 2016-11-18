#include "MatchServer.h"
#include "AppConfig.h"

void main() {
	AppConfig* config = new AppConfig();
	config->GetAppConfig();
}
