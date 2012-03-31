#pragma once

#include "ComposantsCadre.h"


/*
 * BOUTON ARMELIORE ARME 1
 */
class BoutonAmelioreArme1 : public ComposantCadre
{
public:
	BoutonAmelioreArme1();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};