#include "MatchServer.h"
#include "AppConfig.h"
#include "Logger.h"
#include "IOCPManager.h"

void main() {
	// logger ��� ���� 
	Logger& logger = Logger::GetInstance();
	logger.Info("con ",123131321,"verge ",11111,"���K�����K��");

	AppConfig config = AppConfig::GetInstance();
	config.GetAppConfig();
	
	IOCPManager* iocp = IOCPManager::GetInstance();
	iocp->Start();
	MatchServer* ms = new MatchServer();
	ms->Initailize();
	ms->Start();
	while (true) {}
}
