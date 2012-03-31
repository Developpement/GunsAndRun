#pragma once


#include "Gestionnaire.h"
//#include "ConfigurationJeu.h"
//#include "Debug.h"
#include "Texte.h"
#include <sstream>
#include <string>
using namespace std;

class Gestionnaire;

enum TypeBouttons {
	BOUTTONS_SELECTION_ARME=0,
	BOUTTONS_MODIFICATIONS_ARME,
	BOUTTONS_APTITUDE_PERSONNAGE,
	BOUTTONS_MENU,
	BOUTONS_INACTIF
};


class ComposantCadre
{
public:
	TypeBouttons typeBouttons;

	int posX,posY; // position de l'image sur l'écran
	Gestionnaire* application;
	ConfigurationJeu* configuration;
	Debug* debug;

	vector<SDL_Surface*>* animation;
	vector<SDL_Surface*>::iterator imageCourante;

	string type;

	ComposantCadre();
	virtual bool init()=0;
	virtual bool load()=0;
	virtual bool draw(SDL_Surface* screen)=0;
	virtual void changeImage(string& nom);
	virtual bool action()=0;
	bool estClique(Uint16& x, Uint16& y);
};


