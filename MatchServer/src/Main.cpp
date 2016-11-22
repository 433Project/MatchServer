#include "MatchServer.h"
#include "AppConfig.h"
#include "Logger.h"
#include "IOCPManager.h"

void main() {
	// logger 사용 예시 
	Logger& logger = Logger::GetInstance();
	logger.Info("con ",123131321,"verge ",11111,"킇핳하하핳ㅎ");
	logger.Info("↑성공하셔서 신나셨어요?");

	AppConfig config = AppConfig::GetInstance();
	config.GetAppConfig();

	cout << config.GetAppConfig() << endl;
	cout << config.GetConfig<json>("max") << endl;
	
	// appconfig(json)에 새로운 값 대입 예시
	config.GetAppConfig()["wow"] = "adf";
	cout << config.GetAppConfig() << endl;
	
	IOCPManager* iocp = IOCPManager::GetInstance();
	iocp->Start();
	MatchServer* ms = new MatchServer();
	ms->Initailize();
	ms->Start();
	while (true) {}
}
