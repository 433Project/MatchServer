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
	bool SendMessage(Socket socket, byte[] buf);
	bool ReceiveMessage(Socket socket);
};

