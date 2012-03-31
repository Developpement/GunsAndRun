#pragma once

#include <cstdlib>
#include <ctime>
using namespace std;

class Aleatoire
{

	static Aleatoire* _singleton;

	Aleatoire();

public:
	static Aleatoire* getInstance();
	static Aleatoire* destruction();

	double getMinMax(double& minmax);	
};