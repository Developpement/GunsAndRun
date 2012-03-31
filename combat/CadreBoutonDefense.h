#pragma once

#include "ComposantsCadre.h"

/*
 * BOUTON DEFENSE
 */
class BoutonDefense : public ComposantCadre
{
public:
	BoutonDefense();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};