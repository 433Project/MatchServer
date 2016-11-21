#include "MatchServer.h"
#include "AppConfig.h"
#include "Logger.h"
#include "IOCPManager.h"

void main() {

	Logger& logger = Logger::GetInstance();
	string msg = logger.convert("123", "12312313", 12);

	cout << msg << endl;
	
	//logger.ERROR("plain str");
	//logger.ERROR("str + int" + 123);
	//logger.INFO("str","st123",12);

	while (true) {}
	AppConfig config = AppConfig::GetInstance();
	//config.GetAppConfig();
	cout << config.GetAppConfig() << endl;
	IOCPManager* iocp = IOCPManager::GetInstance();
	iocp->Start();
	MatchServer* ms = new MatchServer();
	ms->Initailize();
	ms->Start();
	//while (true) {}
}
