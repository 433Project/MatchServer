#pragma once
#include <deque>
#include "Client.h"

using namespace std;

struct WaitingRoom {

	deque<Client> clientList;
};

typedef WaitingRoom ROOM;
typedef ROOM* WaitingList; 