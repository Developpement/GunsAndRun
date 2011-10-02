#pragma once

#include "Outils.h"
#include "conversions.h"
#include "Configuration.h"
#include "definitions.h"
#include "Affichage.h"

#include <SDL_image.h>
#include <SDL.h>
#include <string>
#include <map>
#include <cmath>
using namespace std;


/**
* \enum indiceEtatAnimation
* \brief Enumère les différents états dans lequel peut se trouve une unité.
*/
enum indiceEtatAnimation {
	IMMOBILE = 0,
	DEPLACE = 1,
	ATTAQUE = 2,
	DEPLACE_ET_ATTAQUE = 3
};



/**
* \class Surfaces
* \brief Sert de conteneur pour l'ensemble des surfaces.
*/
class Surfaces
{
	/*! Unique objet contenant toutes les surfaces. Evite duplication. */
	static Surfaces* _singleton;

	/*! Liste des animation indexées par nom. */
	map<string,vector<SDL_Surface*>> animList;
	/*! A chaque animation correspond une boite de collisions. */
	map<string,vector<SDL_Rect>> collisionList;

	/*! Permet d'utiliser les fichiers de configuration pour charger les images. */
	Configuration* configuration;

	/*! Constructeur de la classe Surfaces. */
	Surfaces();

public:

	
	/**
	* \brief Force l'existance unique d'un objet Surfaces.
	* \details La première fois que la méthode est appelée, une instance de la classe est crée. Les fois suivantes, seul le pointeur vers la première instance est appelée
	* 			et aucune autre instance n'est créée.
	* \return Le pointeur vers l'unique instance de type Surfaces.
	*/
	static Surfaces* getInstance();

	/**
	* \brief Libère la mémoire allouée à l'unique instance de la classe Surfaces.
	* \return Pointeur vers l'adresse 0.
	*/
	static Surfaces* destruction();
	
	/**
	* \brief charge toutes les animations et les boitiers de collision à partir de cette méthode.
	* \details Cette méthode ne charge les images que si le conteneur est vide.
	* \return true en cas de succès, false en cas d'échec.
	*/
	bool load();

	
	int addAnimation (string Animation, string imageNeutre);
	int addCollisionBox(string Animation, string imageNeutre);
	
	vector<SDL_Surface*>* getAnimation (const char* nomAnimation);
	vector<SDL_Surface*>* getAnimation (const char* name, int& largeur, int& hauteur);

	pair<int,int> getSizeAnimationFirstImage (const char* name);
	
	vector<SDL_Rect>* getBoitesCollisions (const char* name);
	vector<SDL_Rect>* getBoitesCollisions (const char* name, int& largeur, int& hauteur);
	
	
};

