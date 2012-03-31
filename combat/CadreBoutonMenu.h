#pragma once

#include "ComposantsCadre.h"

/*
 * BOUTON MENU
 */
class BoutonMenu : public ComposantCadre
{
public:
	BoutonMenu();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};