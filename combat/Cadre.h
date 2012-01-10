#pragma once

//#include "Gestionnaire.h"
#include "DisplayFormatSurfaces.h"
#include "ConfigurationJeu.h"
#include "Affichage.h"
#include "Outils.h"
#include "Bouton.h"
#include "Debug.h"
#include <SDL/SDL.h>
#include <vector>
#include <map>
using namespace std;

class Gestionnaire;
class Bouton;
class BoutonArme1;
class BoutonArme2;
class BoutonArme3;
class BoutonArme4;


class Cadre
{
	static Cadre* _singleton;
	Cadre();
	~Cadre();

public:

	ConfigurationJeu* configuration;
	Gestionnaire* application;
	Surfaces* surfaces;
	Debug* debug;

	vector<SDL_Surface*>* animation;
	vector<SDL_Surface*>::iterator imageCourante;
	vector<SDL_Rect>* boitesCollisions;

	// On utilise un vecteur de pointeurs, car il n'est pas possible d'instancier une classe virtuelle pure dans un conteneur de type vector
	vector<Bouton*> boutonsCadre;

	bool doitEffectuerUneAction;
	int posX,posY;

	
	bool actionSouris(int& X, int& Y);
	//bool detecteCollisions(int decalX, int decalY);
	int load();
	int update();
	int selectionBouton(Uint16& X, Uint16& Y);
	int draw(SDL_Surface* screen);

	bool changeImageBouttonArme (string& nom);

	static Cadre* getInstance();
	static Cadre* destruction();


};
