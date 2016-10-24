#pragma once

#include <iostream>
#include "ClientHolder.h"
#include "Client.h"
#include <map>

using namespace std;


// MS에 요청한 Client들의 정보를 관리한다.
class ClientHolder
{

public:
	ClientHolder();
	~ClientHolder();

private: 

	map<string, Client> clientMap;



};

