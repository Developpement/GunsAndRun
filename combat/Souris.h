#pragma once

#include "Debug.h"
#include "Background.h"
#include "Gestionnaire.h"
#include "Cadre.h"
#include "Unite.h"
#include <SDL/SDL.h>


//class Cadre;

/**
* \class Souris
*/
class Souris
{
	static Souris* _singleton;

	Debug* debug;
	//Gestionnaire* gestionnaire;
	//Cadre* cadre;

	Souris();
	

public:
	bool isLeftMouseClickOnCadre;
	bool isLeftMouseClickOnBackground;


	void handleInput(SDL_Event& event);

	static Souris* getInstance();
	static Souris* destruction();
};