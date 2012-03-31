#pragma once

#include "ComposantsCadre.h"

/*
 * BOUTON SUPPRIME ARME 3
 */
class BoutonSupprimeArme3 : public ComposantCadre
{
public:
	BoutonSupprimeArme3();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};