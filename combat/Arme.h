#pragma once

#include "Application.h"
#include "Balle.h"
#include "DisplayFormatSurfaces.h"
#include "Affichage.h"
#include "Outils.h"
#include <SDL.h>
#include <vector>
#include <map>
using namespace std;

#define MAX_BALLES 300

//class UsineArmes;
class UsineBalles;
class Application;
class Unite;

class Arme 
{
public:
	Application* application;
	Surfaces* surfaces;
	UsineBalles* usineBalles;
	

	int typeUnite;
	int identifiantJoueur;

	string type;
	string sousTypeBalle;

	int cadence;
	int degat;
	double angle;
	bool tir;

	vector<SDL_Surface*>* animation;
	vector<SDL_Surface*>::iterator imageCourante;
	vector<SDL_Rect>* boitesCollisions;


	//Les coordonn�es x et y du point
    float posX, posY;

    //La vitesse du point
    float velX, velY;

	template <typename T>
	Arme(T posX, T posY, double& angle, string& typeArme, string& typeBalle, int typeUnite, int identifiantJoueur);
	int handleInput(SDL_Event& event);
	int load();
	int update();
	void updateAngle(double& angle);
	int debutTir ();
	int	arretTir();
	int draw(SDL_Surface* screen);

	Arme* clone();
};



template <typename T>
Arme::Arme(T posX, T posY, double& angle, string& typeArme,string& typeBalle, int typeUnite, int identifiantJoueur)
{
	this->type=typeArme;
	this->sousTypeBalle=typeBalle;

	this->typeUnite= typeUnite;
	application=Application::getInstance();
	surfaces=Surfaces::getInstance();
	usineBalles=UsineBalles::getInstance();

	load();
	
	this->identifiantJoueur = identifiantJoueur;
	this->posX = static_cast<float>(posX);
	this->posY = static_cast<float>(posY);
	velX = 1;
	velY = 1;
	cadence = 1;
	this->angle=angle;
}



//-----------------------------------------------------------------------------------------------
class UsineArmes
{
	static UsineArmes* _singleton;
	map<string, Arme*> modelesArmes;

	UsineArmes();
	bool chargement();

public:

	static UsineArmes* getInstance();
	static UsineArmes* destruction();
	template <typename T>
	Arme* creationArme(T posX, T posY, double& angle, string& typeArme, int typeUnite, int identifiantJoueur);
};

template <typename T>
Arme* UsineArmes::creationArme(T posX, T posY, double& angle, string& typeArme, int typeUnite, int identifiantJoueur)
{
	map<string,Arme*>::iterator it = modelesArmes.find(typeArme);
	if(it!=modelesArmes.end()) {
		Arme* nouvelleArme = it->second->clone();
		nouvelleArme->posX = static_cast<float>(posX);
		nouvelleArme->posY = static_cast<float>(posY);
		nouvelleArme->angle = angle;
		nouvelleArme->identifiantJoueur = identifiantJoueur;
		nouvelleArme->typeUnite = typeUnite;

		return nouvelleArme;
	}
	else return 0;
}