#pragma once

#include "Horloge.h"
#include "Musique.h"
#include "Cadre.h"
#include "Background.h"
#include "Unite.h"
#include "DisplayFormatSurfaces.h"
#include "Affichage.h"
#include "Conversions.h"
#include "ConfigurationJeu.h"
#include "definitions.h"
#include "Debug.h"
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL.h>

#include <list>

/**
* \class KeyValue
* \brief Contient l'état des touches et souris.
*/
class KeyValue
{
public:
	bool isArrowUpPressed;
	bool isArrowLeftPressed;
	bool isArrowDownPressed;
	bool isArrowRightPressed;
	bool isLeftMouseClickOnCadre;
	bool isLeftMouseClickOnBackground;

	KeyValue()
	{
		isArrowUpPressed=false;
		isArrowLeftPressed=false;
		isArrowDownPressed=false;
		isArrowRightPressed=false;
		isLeftMouseClickOnCadre=false;
		isLeftMouseClickOnBackground=false;
	}
};


class Cadre;
class Background;
class Unite;
class Balle;


/**
* \class Gestionnaire
* \brief Classe principale, utilisant toutes les autres classes et méthodes. Gère les timers, la musique, les créations et destructions d'objets,...
*/
class Gestionnaire
{
	static Gestionnaire* _singleton;

	bool gameover;
	/*! Pointeur vers l'instance unique de la configuration du jeu. */
	ConfigurationJeu* configuration;
	/*! Liste des images chargées en mémoire. */
	Surfaces* surfaces;
	/*! Permet l'utilisation de musique et de sons. */
	//Musique* musique;

	/*! Les Horloge */
	Horloge* timers;

	Debug* debug;


	/**
	* \brief Constructeur de la classe application. Initialise quelques variables.
	*/
	Gestionnaire();

	/**
	* \brief Destructeur de la classe Gestionnaire. Libère la mémoire allouée dynamiquement.
	*/
	~Gestionnaire();


public:
	/*! enregistre l'etat des entrées clavie r et souris. */
	KeyValue keyValue;
	pair<float, float> resolution;

	list<Unite*> unitees;
	list<Balle*> balles;
	Background* background;
	Cadre* cadre;

	int idCpt;

	int windowWidth,windowHeight;
	SDL_Surface* screen;


	//ConfigurationJeu configuration;
	SDL_Event event;

	// methodes
	static Gestionnaire* getInstance();
	static Gestionnaire* destruction();

	int init ();
	//int load ();
	int update ();
	int draw ();
	void close();


};
