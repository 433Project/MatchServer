#pragma once
#include <string>

using namespace std;


struct UserInfo
{
	int	ID;
	int	metric;
};

enum ClientState : int {
	Waiting,
	Reserved
};

struct Policy {

public: 
	static const int MATCHING_INTERVAL = 500; // 500ms
	static const int MATCHING_ATTEMPT = 3; // 3È¸ ½Ãµµ 
};

