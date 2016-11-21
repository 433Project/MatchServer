#include "MatchServer.h"
#include "AppConfig.h"
#include "Logger.h"

void main() {
	AppConfig config = AppConfig::GetInstance();
	config.GetAppConfig();
	while (true) {}
}
