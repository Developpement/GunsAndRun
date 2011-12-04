#pragma once

#include "Debug.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string>

#include <iostream>
#include <vector>
using namespace std;



enum listeTimers
{
    TIMER_AFFICHE=0,
    TIMER_UPDATE,
    TIMER_END
};



/**
* \brief
*/
class Timers
{
    static Timers* singleton;

	Debug* debug;

    int temps[TIMER_END];

    //Le temps quand le timer est lancé
    int millisecondes;
    Timers();

    public:

    static Timers* getInstance();
    static Timers* destruction();

    void raffraichissement();
    bool lanceToutesLesMs(int millisecondes, listeTimers unTimer);
	bool timerInferieurHorloge(int& timer);
	void horlogePlusDelai(int& timer, int& delai);

};




