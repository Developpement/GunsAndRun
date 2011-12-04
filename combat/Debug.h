#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iostream>
using namespace std;

static const char logFileName[] = "log.txt";




class Debug
{
	int logNb;

	static Debug* _singleton;

	Debug();


public:

	static Debug* getInstance();
	static Debug* destruct();

	void print(string& msg);
	void print(char* msg);

};
