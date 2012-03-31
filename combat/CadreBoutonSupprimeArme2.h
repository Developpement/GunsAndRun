#pragma once

#include "ComposantsCadre.h"

/*
 * BOUTON SUPPRIME ARME 2
 */
class BoutonSupprimeArme2 : public ComposantCadre
{
public:
	BoutonSupprimeArme2();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};