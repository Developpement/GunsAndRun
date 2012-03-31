#pragma once

#include "ComposantsCadre.h"
//#include "Cadre.h"
#include "Texte.h"


/*
 * \brief Repr�sente dans le cadre sup�rieur la somme d'argent 
 *        d�tenue par le joueur.
 */
class CadreCoffre : public ComposantCadre
{
	Texte* argent;
	int valeur;
	int posXArgent,posYArgent;

public:
	CadreCoffre();
	~CadreCoffre();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};