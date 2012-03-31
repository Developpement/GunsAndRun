#pragma once

#include "ComposantsCadre.h"

/*
 * BOUTON SUPPORT
 */
class BoutonSupport : public ComposantCadre
{
public:
	BoutonSupport();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};