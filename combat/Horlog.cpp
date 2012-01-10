#include "Horloge.h"

Horloge* Horloge::singleton=0;



Horloge::Horloge()
{
	debug=Debug::getInstance();

    for(unsigned int i=0;i<sizeof(listeHorloge);i++) {
        temps[i]=0;
    }
    raffraichissement();
}



Horloge* Horloge::getInstance()
{
    if(singleton==0)
        singleton=new Horloge();

    return singleton;
}

Horloge* Horloge::destruction()
{
    if(singleton!=0)
        delete singleton;
    return singleton;
}

void Horloge::raffraichissement()
{
    millisecondes=SDL_GetTicks();
}

bool Horloge::lanceToutesLesMs(int periode, listeHorloge unTimer)
{
    if(millisecondes>=temps[unTimer]) {
        temps[unTimer]=millisecondes+periode;
        return true;
    }
    return false;
}

bool Horloge::timerInferieurHorloge(int& timer)
{
	if(timer<millisecondes)
		return true;
	return false;
}

void Horloge::horlogePlusDelai(int& timer, int& delai)
{
	timer=millisecondes+delai;
}