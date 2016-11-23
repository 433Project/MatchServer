#include "MatchServer.h"

MatchServer::MatchServer()
{
	iocp = IOCPManager::GetInstance();
	socket = SocketManager::GetInstance();

}

MatchServer::~MatchServer()
{
	WSACleanup();
}

void MatchServer::Initailize() 
{
	WSADATA wsd;
	int nErrCode = WSAStartup(MAKEWORD(2, 2), &wsd);
	if (nErrCode)
	{
		logger.Error("WSAStartup fail : ", nErrCode);
		return;
	}
}

void MatchServer::Start() 
{
	//1. listen socket
	logger.Info("Listen Socket");
	if (socket->CreateListenSocket())
	{
		socket->AcceptEX(5);
	}
	else 
	{
		exit(0);
	}
	
	//2. config server
	logger.Info("Config Server");
	json cf = config.GetConfig<json>("Config");

	cout << cf << endl;
	string ip = cf["ip"];
	if(true)
		socket->CreateSocket(CONFIG, ip, cf["port"]);
	else
		socket->CreateSocket(CONFIG, cfIP, cfPort);

	//3. connection server  
	logger.Info("Connection Server");
	json cs = config.GetConfig<json>("Connection");
	bool connected;
	if (true)
		connected = socket->CreateSocket(CONFIG, cs["ip"], cs["port"]);
	else
		connected = socket->CreateSocket(CONFIG, csIP, csPort);

	if (!connected)
	{
		exit(0);
	}
}
