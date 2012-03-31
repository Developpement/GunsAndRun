#pragma once

#include "ComposantsCadre.h"

/*
 * BOUTON ARME 1
 */
class BoutonArme1 : public ComposantCadre
{
public:
	BoutonArme1();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};