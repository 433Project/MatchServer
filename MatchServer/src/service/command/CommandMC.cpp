#include "CommandMC.h"
#include "SocketManager.h"
#include "MessageManager.h"

CommandMC::CommandMC()
{
	msgM = new MessageManager();
	socketM = SocketManager::GetInstance();

	func = new FuncType[funcCount];
	func[0] = &CommandMC::Command_MATCH_REQUEST;
	func[1] = &CommandMC::Command_MATCH_RESPONSE;
}


CommandMC::~CommandMC()
{
	for (int i = 0; i < funcCount; i++)
	{
		delete &func[i];
	}
	delete func;
	if (msgM != nullptr)
		delete msgM;
}

void CommandMC::CommandMCHandler(Packet* p)
{
		(this->*func[p->body->cmd() - this->cmd])(p);
}

void CommandMC::Command_MATCH_REQUEST(Packet* p)
{
	//1)client holder에 저장하기
	//2)매트릭 생성하기
	//3)노티매칭req
}

void CommandMC::Command_MATCH_RESPONSE(Packet* p)
{
	//이건 받을수 없어
}
