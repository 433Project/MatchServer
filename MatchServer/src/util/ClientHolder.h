#pragma once

#include <iostream>
#include "ClientHolder.h"
#include "Client.h"
#include <map>

using namespace std;


// MS�� ��û�� Client���� ������ �����Ѵ�.
class ClientHolder
{

public:
	ClientHolder();
	~ClientHolder();

private: 

	map<string, Client> clientMap;



};

