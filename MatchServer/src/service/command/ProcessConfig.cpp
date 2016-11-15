//#include "ProcessConfig.h"
//#include "MessageManager.h"
//
//MessageManager *mm;
//
//ProcessConfig::ProcessConfig()
//{
//	mm = new MessageManager();
//}
//
//ProcessConfig::~ProcessConfig()
//{
//}
//
//
//void ProcessConfig::CommandMSID(SOCKET s, Header* h, Body* b) 
//{
//	cout << "My ID : " << b->data()->c_str() << endl;
//	char* data = mm->MakePacket(CONFIG_SERVER, 0, Command_MSLIST_REQUEST, Status_NONE, "");
//	mm->SendPacket(s, data);
//}
//
//void ProcessConfig::CommandMSList(SOCKET s, Header* h, Body* b)
//{
//}
