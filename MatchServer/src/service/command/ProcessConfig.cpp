#include "ProcessConfig.h"
#include "MessageManager.h"
//MessageManager *mm;
ProcessConfig::ProcessConfig()
{
	//mm = new MessageManager();
}

ProcessConfig::~ProcessConfig()
{
}

/*
void ProcessConfig::Process(SOCKET s, Header* h, Body* b) 
{
	if (b->cmd() == Command_MS_ID)
	{
		cout << "My ID : " << b->data()->c_str() << endl;
		char* data = mm->MakePacket(CONFIG_SERVER, 0, Command_MSLIST_REQUEST, Status_NONE, "");
		mm->SendPacket(ioData->hClntSock, data);
	}
	else if (b->cmd() == Command_MSLIST_RESPONSE)
	{
		if (b->status() == Status_SUCCESS)
		{
			SOCKET s = sm->GetConnectSocket("MS", (char*)b->data()->c_str(), 12000);
			if (s != INVALID_SOCKET)
				AssociateDeviceWithCompletionPort(hCompletion, (HANDLE)s, KEY_MATCH_SERVER);
			else
				closesocket(s);
		}
	}
}*/
