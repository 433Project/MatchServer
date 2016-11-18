#include "MatchServer.h"
#include "AppConfig.h"

void main() {
	AppConfig config = AppConfig::GetInstance();
	config.GetAppConfig();
	while (true) {}
}
