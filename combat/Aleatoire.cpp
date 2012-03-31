#include "Aleatoire.h"

Aleatoire* Aleatoire::_singleton = 0;



Aleatoire* Aleatoire::getInstance()
{
	if(_singleton==0)
		_singleton=new Aleatoire();
	return _singleton;
}

Aleatoire* Aleatoire::destruction()
{
	if(_singleton) {
		delete _singleton;
		_singleton=0;
	}
	return _singleton;
}


Aleatoire::Aleatoire()
{
  srand (static_cast<unsigned int>(time(NULL)) );
}
#include <iostream>

double Aleatoire::getMinMax(double& minmax)
{
   int aleatoire = rand();
   if(aleatoire%2==0)
	   return ( aleatoire/(double)RAND_MAX ) * (minmax);
   else return -( aleatoire/(double)RAND_MAX ) * (minmax);
}