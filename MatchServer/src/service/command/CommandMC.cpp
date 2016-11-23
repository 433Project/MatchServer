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
	//1)client holder�� �����ϱ�
	//2)��Ʈ�� �����ϱ�
	//3)��Ƽ��Īreq
}

void CommandMC::Command_MATCH_RESPONSE(Packet* p)
{
	//�̰� ������ ����
}
