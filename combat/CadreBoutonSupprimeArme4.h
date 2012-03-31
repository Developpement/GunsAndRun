#pragma once

#include "ComposantsCadre.h"



/*
 * BOUTON SUPPRIME ARME 4
 */
class BoutonSupprimeArme4 : public ComposantCadre
{
public:
	BoutonSupprimeArme4();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};