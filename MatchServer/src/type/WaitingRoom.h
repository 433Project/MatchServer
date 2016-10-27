#pragma once
#include <iostream>
#include <deque>
#include "Client.h"

using namespace std;

struct WaitingRoom {

	deque<Client> clientList;
};

//
//typedef WaitingRoom* PTRWaitingRoom;
//typedef PTRWaitingRoom* WAITINGLIST;

typedef WaitingRoom ROOM;
typedef ROOM* WaitingList; 