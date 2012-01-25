#pragma once


#include "Gestionnaire.h"




class Batiment
{
public:
	Gestionnaire* application;
	ConfigurationJeu* configuration;
	Surfaces* surfaces;

	Debug* debug;

	vector<SDL_Surface*>* animation;
	vector<SDL_Surface*>::iterator imageUniteCourante;
	vector<SDL_Rect>* boitesCollisions;

	string typeBatiment;

	int identifiantJoueur;
	
	int vie;
	//Les coordonnées x et y du point
	float posX, posY;
	float velX, velY;

	Batiment();
	
	virtual int handleInput(SDL_Event& event)=0;
	virtual int load()=0;
	virtual int update()=0;
	virtual int draw(SDL_Surface* screen)=0;
};


class Marche : public Batiment
{
public:
	Marche(int posX, int posY);

	virtual int load();
	virtual int update();
	virtual int handleInput(SDL_Event& event);
	virtual int draw(SDL_Surface* screen);
};