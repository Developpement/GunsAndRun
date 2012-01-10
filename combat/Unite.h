#pragma once

//#include "Gestionnaire.h"
#include "Arme.h"
#include "DisplayFormatSurfaces.h"
#include "ConfigurationJeu.h"
#include "Affichage.h"
#include "Outils.h"
#include "Conversions.h"
#include "Debug.h"
#include <SDL/SDL.h>
#include <vector>
#include <map>
using namespace std;

class Arme;
class UsineArmes;
//class Gestionnaire;

enum typeUniteControle {
	NON_DEFINI,
	PJOUEUR_JOUABLE,
	PJOUEUR_NONJOUABLE,
	PNON_JOUEUR
};



class Unite
{
public:
	Gestionnaire* application;
	ConfigurationJeu* configuration;
	Surfaces* surfaces;

	Debug* debug;

	Arme* arme;
	UsineArmes* usineArmes;

	vector<SDL_Surface*>* animation;
	vector<SDL_Surface*>::iterator imageUniteCourante;
	vector<SDL_Rect>* boitesCollisions;

	string typeArme;
	string typeBalle;

	int identifiantJoueur;
	double angle;
	int etat;
	typeUniteControle typeUnite;

	int vie;
	//Les coordonnées x et y du point
   float posX, posY;

   //La vitesse du point
   float velX, velY;

	Unite();

	virtual int load()=0;
	virtual int update()=0;
	virtual int handleInput(SDL_Event& event)=0;
	virtual int draw(SDL_Surface* screen)=0;
};

/**
* \brief
*/
class UniteJoueurJouable : public Unite
{
public:
	UniteJoueurJouable(int& posX, int& posY, string& typeArme, string& typeBalle);

	virtual int load();
	virtual int update();
	virtual int handleInput(SDL_Event& event);
	virtual int draw(SDL_Surface* screen);
};

/**
* \brief
*/
/*
class UniteJoueurNonJouable : public Unite
{
public:
	UniteJoueurNonJouable(int& posX, int& posY);

	virtual int load();
	virtual int update();
	virtual int handleInput(SDL_Event& event);
	virtual int draw(SDL_Surface* screen);
};
*/

/**
* \brief
*/
class UniteNonJoueur : public Unite
{
public:
	UniteNonJoueur(int& posX, int& posY, string& typeArme, string& typeBalle);

	virtual int load();
	virtual int update();
	virtual int handleInput(SDL_Event& event);
	virtual int draw(SDL_Surface* screen);
};



