#pragma once
#include "common.h"
#include <iostream>
#include <queue>
#include <D>

using namespace std;

struct WaitingRoom {

	int count;
	unordered_map<CLIENTID, Client> clientList;

};

//
//typedef WaitingRoom* PTRWaitingRoom;
//typedef PTRWaitingRoom* WAITINGLIST;

typedef WaitingRoom ROOM;
typedef ROOM* WaitingList; 