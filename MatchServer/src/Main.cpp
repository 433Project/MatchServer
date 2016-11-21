#include "MatchServer.h"
#include "AppConfig.h"
#include "IOCPManager.h"

void main() {
	AppConfig config = AppConfig::GetInstance();
	config.GetAppConfig();
	IOCPManager* iocp = IOCPManager::GetInstance();
	iocp->Start();
	MatchServer* ms = new MatchServer();
	ms->Initailize();
	ms->Start();
	while (true) {}
}
