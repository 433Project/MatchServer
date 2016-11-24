#include "MatchServer.h"
#include "AppConfig.h"
#include "Logger.h"
#include "IOCPManager.h"

void main() {
	// logger 사용 예시 
	Logger& logger = Logger::GetInstance();
	logger.Info("con ",123131321,"verge ",11111,"킇핳하하핳ㅎ");

	AppConfig config = AppConfig::GetInstance();
	config.GetAppConfig();
	
	IOCPManager* iocp = IOCPManager::GetInstance();
	iocp->Start();
	MatchServer* ms = new MatchServer();
	ms->Initailize();
	ms->Start();
	while (true) {}
}
