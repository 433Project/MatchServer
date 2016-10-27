#pragma once
#include <iostream>
#include <winsock2.h>
#include <MSWSock.h>

class MessageManager
{
public:
	MessageManager();
	~MessageManager();

private:
	bool SendMessage(SOCKET socket);
	bool ReceiveMessage(SOCKET socket);
};

