#pragma once

//#include "Application.h"
#include "DisplayFormatSurfaces.h"
#include "Configuration.h"
#include "Affichage.h"
#include "Outils.h"
#include "Bouton.h"
#include "Debug.h"
#include <SDL/SDL.h>
#include <vector>
#include <map>
using namespace std;

class Application;
class Bouton;
class BoutonArme1;
class BoutonArme2;
class BoutonArme3;
class BoutonArme4;

class Cadre
{
public:
	Configuration* configuration;
	Application* application;
	Surfaces* surfaces;
	Debug* debug;

	vector<SDL_Surface*>* animation;
	vector<SDL_Surface*>::iterator imageCourante;
	vector<SDL_Rect>* boitesCollisions;

	// On utilise un vecteur de pointeurs, car il n'est pas possible d'instancier une classe virtuelle pure dans un conteneur de type vector
	vector<Bouton*> boutonsCadre;
	/*BoutonArme1* boutonArme1;
	BoutonArme2* boutonArme2;
	BoutonArme3* boutonArme3;
	BoutonArme4* boutonArme4;*/


	bool doitEffectuerUneAction;
	int posX,posY;

	Cadre(int &posX, int &posY, Configuration *config, Surfaces *surfaces, Application* application);
	bool actionSouris(int& X, int& Y);
	//bool detecteCollisions(int decalX, int decalY);
	int load();
	int update();
	int handleInput(SDL_Event& event);
	int draw(SDL_Surface* screen);
};
