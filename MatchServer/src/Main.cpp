#include "MatchServer.h"
#include "AppConfig.h"
#include "Logger.h"
#include "IOCPManager.h"

void main() {
	// logger ��� ���� 
	Logger& logger = Logger::GetInstance();
	logger.Info("con ",123131321,"verge ",11111,"���K�����K��");
	logger.Info("�輺���ϼż� �ų��̾��?");

	AppConfig config = AppConfig::GetInstance();
	config.GetAppConfig();

	cout << config.GetAppConfig() << endl;
	cout << config.GetConfig<json>("max") << endl;
	
	// appconfig(json)�� ���ο� �� ���� ����
	config.GetAppConfig()["wow"] = "adf";
	cout << config.GetAppConfig() << endl;
	
	IOCPManager* iocp = IOCPManager::GetInstance();
	iocp->Start();
	MatchServer* ms = new MatchServer();
	ms->Initailize();
	ms->Start();
	while (true) {}
}
