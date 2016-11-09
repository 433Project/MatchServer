#pragma once
#include "Packet_generated.h"
#include <string>

using namespace fb;
using namespace std;

class Message {

public :
	Command cmd;
	Status status;
	char* data;
};