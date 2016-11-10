#pragma once
#include <string>
#include <iostream>

using namespace std;

class ConsoleLogger {
	
public :
	static void PrintMessage(string msg) {
		cout << "=====================================================" << endl;
		cout << msg << endl;
		cout << "=====================================================" << endl;
	}

};