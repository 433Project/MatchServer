#include "MessageManager.h"


MessageManager::MessageManager()
{
}


MessageManager::~MessageManager()
{
}

void MessageManager::SendMessage(SOCKET socket, LPPER_IO_DATA ov)
{
	WSASend(socket, &(ov->wsaBuf), 1, NULL, 0, ov, NULL);
}

void MessageManager::ReceiveMessage(SOCKET socket, LPPER_IO_DATA ov)
{
	WSARecv(socket, &(ov->wsaBuf), 1, NULL, 0, ov, NULL);
}
