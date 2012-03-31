#pragma once

#include "ComposantsCadre.h"

/*
 * BOUTON ARMELIORE ARME 2
 */
class BoutonAmelioreArme2 : public ComposantCadre
{
public:
	BoutonAmelioreArme2();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};