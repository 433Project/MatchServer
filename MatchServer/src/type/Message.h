#pragma once
#include "Packet_generated.h"
#include <string>

using namespace fb;
using namespace std;

class Message {

public :
	Command cmd;
	string data;


};