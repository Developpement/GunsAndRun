#pragma once

#include "ComposantsCadre.h"


/*
 * BOUTON VIE
 */
class CadreBoutonVie : public ComposantCadre
{
public:
	CadreBoutonVie();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};