#pragma once

#include "Debug.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string>

#include <iostream>
#include <vector>
using namespace std;



enum listeHorloge
{
    TIMER_AFFICHE=0,
    TIMER_UPDATE,
    TIMER_END
};



/**
* \brief
*/
class Horloge
{
    static Horloge* singleton;

	Debug* debug;

    int temps[TIMER_END];

    //Le temps quand le timer est lanc�
    int millisecondes;
    Horloge();

    public:

    static Horloge* getInstance();
    static Horloge* destruction();

    void raffraichissement();
    bool lanceToutesLesMs(int millisecondes, listeHorloge unTimer);
	bool timerInferieurHorloge(int& timer);
	void horlogePlusDelai(int& timer, int& delai);

};




