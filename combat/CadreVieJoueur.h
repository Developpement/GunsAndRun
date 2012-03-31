#pragma once

#include "ComposantsCadre.h"


/*
 * BOUTON VieJoueur
 */
class CadreVieJoueur : public ComposantCadre
{
	int valeur;
	SDL_Surface* viePerdue;
	int posXViePerdue, posYViePerdue;

public:
	CadreVieJoueur();
	~CadreVieJoueur();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
	void setVie(int& valeur, int& max);
};
