#pragma once

#include "Debug.h"
#include "Background.h"
#include "Gestionnaire.h"
#include <SDL/SDL.h>

#define AUCUNE_FLECHE_PRESSEE   0x00000000
#define FLECHE_HAUT_PRESSEE		0x00000001
#define FLECHE_BAS_PRESSEE		0x00000002
#define FLECHE_GAUCHE_PRESSEE	0x00000004
#define FLECHE_DROITE_PRESSEE   0x00000008


class Background;


/**
* \class KeyValue
* \brief Contient l'état des touches et souris.
*/
class Clavier
{
	static Clavier* _singleton;

	Debug* debug;


	Clavier();
	//~Clavier();

public:
	int etatClavier;

	void handleInput(SDL_Event& event);

	static Clavier* getInstance();
	static Clavier* destruction();
};