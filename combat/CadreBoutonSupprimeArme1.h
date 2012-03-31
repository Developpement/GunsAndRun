#pragma once

#include "ComposantsCadre.h"

/*
 * BOUTON SUPPRIME ARME 1
 */
class BoutonSupprimeArme1 : public ComposantCadre
{
public:
	BoutonSupprimeArme1();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};
