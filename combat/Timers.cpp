#include "Timers.h"

Timers* Timers::singleton=0;



Timers::Timers()
{
	debug=Debug::getInstance();

    for(unsigned int i=0;i<sizeof(listeTimers);i++) {
        temps[i]=0;
    }
    raffraichissement();
}



Timers* Timers::getInstance()
{
    if(singleton==0)
        singleton=new Timers();

    return singleton;
}

Timers* Timers::destruction()
{
    if(singleton!=0)
        delete singleton;
    return singleton;
}

void Timers::raffraichissement()
{
    millisecondes=SDL_GetTicks();
}

bool Timers::lanceToutesLesMs(int periode, listeTimers unTimer)
{
    if(millisecondes>=temps[unTimer]) {
        temps[unTimer]=millisecondes+periode;
        return true;
    }
    return false;
}

bool Timers::timerInferieurHorloge(int& timer)
{
	if(timer<millisecondes)
		return true;
	return false;
}

void Timers::horlogePlusDelai(int& timer, int& delai)
{
	timer=millisecondes+delai;
}