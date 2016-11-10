#pragma once
#include "MessageManager.h"
class ProcessManager
{
public:
	ProcessManager();
	~ProcessManager();
	void ProcessConfigServer(Body* body);
	void ProcessConnectionServer(Body* body);
	void ProcessMatchingServer(Body* body);
};

