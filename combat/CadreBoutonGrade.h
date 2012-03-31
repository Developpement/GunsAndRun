#pragma once

#include "ComposantsCadre.h"

/*
 * BOUTON GRADE
 */
class BoutonGrade : public ComposantCadre
{
public:
	BoutonGrade();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};