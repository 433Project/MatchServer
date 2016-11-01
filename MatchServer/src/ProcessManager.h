#pragma once
class ProcessManager
{
public:
	ProcessManager();
	~ProcessManager();
	void ProcessConfigServer(char* buf);
	void ProcessConnectionServer(char* buf);
	void ProcessMatchingServer(char* buf);
};

