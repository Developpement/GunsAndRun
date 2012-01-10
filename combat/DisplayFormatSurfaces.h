#pragma once

#include "Outils.h"
#include "conversions.h"
#include "ConfigurationJeu.h"
#include "definitions.h"
#include "Affichage.h"
#include "Debug.h"

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <string>
#include <map>
#include <cmath>
using namespace std;


/**
* \enum indiceEtatAnimation
* \brief Enum�re les diff�rents �tats dans lequel peut se trouve une unit�.
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

	Debug* debug;

	/*! Liste des animation index�es par nom. */
	map< string,vector<SDL_Surface*> > animList;
	/*! A chaque animation correspond une boite de collisions. */
	map< string,vector<SDL_Rect> > collisionList;

	/*! Permet d'utiliser les fichiers de configuration pour charger les images. */
	ConfigurationJeu* configuration;

	/*! Constructeur de la classe Surfaces. */
	Surfaces();

public:


	/**
	* \brief Force l'existance unique d'un objet Surfaces.
	* \details La premi�re fois que la m�thode est appel�e, une instance de la classe est cr�e. Les fois suivantes, seul le pointeur vers la premi�re instance est appel�e
	* 			et aucune autre instance n'est cr��e.
	* \return Le pointeur vers l'unique instance de type Surfaces.
	*/
	static Surfaces* getInstance();

	/**
	* \brief Lib�re la m�moire allou�e � l'unique instance de la classe Surfaces.
	* \return Pointeur vers l'adresse 0.
	*/
	static Surfaces* destruction();

	/**
	* \brief charge toutes les animations et les boitiers de collision � partir de cette m�thode.
	* \details Cette m�thode ne charge les images que si le conteneur est vide.
	* \return true en cas de succ�s, false en cas d'�chec.
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

