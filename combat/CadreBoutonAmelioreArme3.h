#pragma once

#include "ComposantsCadre.h"

/*
 * BOUTON ARMELIORE ARME 3
 */
class BoutonAmelioreArme3 : public ComposantCadre
{
public:
	BoutonAmelioreArme3();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};