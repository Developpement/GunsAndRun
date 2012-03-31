#pragma once

#include "ComposantsCadre.h"

/*
 * BOUTON ARME 1
 */
class BoutonArme3 : public ComposantCadre
{
public:
	BoutonArme3();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};