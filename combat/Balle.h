#pragma once

#include "Application.h"
#include "DisplayFormatSurfaces.h"
#include "Affichage.h"
#include "Outils.h"
#include <SDL/SDL.h>
#include <vector>
#include <map>
using namespace std;

//class Application;
class Arme;

class Balle
{
public:
	Application* application;

	vector<SDL_Surface*>* animation;
	vector<SDL_Surface*>::iterator imageCourante;
	vector<SDL_Rect>* boitesCollisions;

	int identifiantJoueur;
	int vie;
	int degats;
	double angle;
	//int etat;

	string type;

	//Les coordonn�es x et y du point
    float vitesse, posX, posY, velX, velY;

	template <typename T>
	Balle(T& posX, T& posY, double angle, string& type, int& identifiantJoueur);

	int load();

	int update();
	int handleInput(SDL_Event& event);
	bool detecteCollisions(float& decalX, float& decalY);
	int draw(SDL_Surface* screen);

	Balle* clone();
};






//-----------------------------------------------------------------------------------------------
class UsineBalles
{
	static UsineBalles* _singleton;
	map<string, Balle*> modelesBalles;

	UsineBalles();
	bool chargement();

public:

	static UsineBalles* getInstance();
	static UsineBalles* destruction();
	template <typename T>
	Balle* creationBalle(T& posX, T& posY, double angle, string& typeBalle, int& identifiantJoueur);
};

template <typename T>
Balle* UsineBalles::creationBalle(T& posX, T& posY, double angle, string& typeBalle, int& identifiantJoueur)
{
	map<string,Balle*>::iterator it = modelesBalles.find(typeBalle);
	if(it!=modelesBalles.end()) {
		Balle* nouvelleBalle = it->second->clone();
		nouvelleBalle->posX = posX;
		nouvelleBalle->posY = posY;
		nouvelleBalle->angle = angle;
		nouvelleBalle->identifiantJoueur = identifiantJoueur;

		nouvelleBalle->posX = (float)posX + ((float)(*(nouvelleBalle->imageCourante))->w)/2;
		nouvelleBalle->posY = (float)posY + ((float)(*(nouvelleBalle->imageCourante))->h)/2;
		nouvelleBalle->velX = angleVersX(nouvelleBalle->vitesse, angle);
		nouvelleBalle->velY = angleVersY(nouvelleBalle->vitesse, angle);
		return nouvelleBalle;
	}
	else return 0;
}
