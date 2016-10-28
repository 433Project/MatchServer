#include "MessageManager.h"


MessageManager::MessageManager()
{

	mm = new MessageManager();
}


MessageManager::~MessageManager()
{
}

void MessageManager::SendPacket(SOCKET socket, char* buf)
{
	//WSASend(socket, &(ov->wsaBuf), 1, NULL, 0, NULL, NULL);
	send(socket, buf, strlen(buf), 0);
}

void MessageManager::ReceivePacket(SOCKET socket, LPPER_IO_DATA ov)
{
	WSARecv(socket, &(ov->wsaBuf), 1, NULL, 0, ov, NULL);
}
