#pragma once


#include "Musique.h"
#include "Cadre.h"
#include "Background.h"
#include "Unite.h"
#include "DisplayFormatSurfaces.h"
#include "Affichage.h"
#include "Conversions.h"
#include "Configuration.h"
#include "definitions.h"
#include <SDL_rotozoom.h>
#include "SDL.h"

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
* \class Application
* \brief Classe principale, utilisant toutes les autres classes et méthodes. Gère les timers, la musique, les créations et destructions d'objets,...
*/
class Application
{
	static Application* _singleton;

	/*! Pointeur vers l'instance unique de la configuration du jeu. */
	Configuration* configuration;
	/*! Liste des images chargées en mémoire. */
	Surfaces* surfaces; 
	/*! Permet l'utilisation de musique et de sons. */
	Musique* musique;


	/**
	* \brief Constructeur de la classe application. Initialise quelques variables.
	*/
	Application();

	/**
	* \brief Destructeur de la classe Application. Libère la mémoire allouée dynamiquement.
	*/
	~Application();


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


	//Configuration configuration;
	SDL_Event event;

	// methodes	
	static Application* getInstance();
	static Application* destruction();

	int init ();
	//int load ();
	int update ();
	int draw ();


};