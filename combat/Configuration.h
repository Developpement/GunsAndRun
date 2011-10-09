#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include "definitions.h"
#ifdef WIN32
#include <TR/DialogueTr.h>
#endif
using namespace std;

/**
* \class Configuration
* \brief Stocke et fournit un acc�s � la configuration du jeu.
*/
class Configuration
{
	/*! La configuration du jeu: <le nom ou r�f�rence, la config ou valeur> */
	map<string,string> config;
	/*! Unique instance de la configuration du jeu. */
	static Configuration* _singleton;

	/**
	* \brief Constructeur de la classe Configuration.
	*/
	Configuration();

	/**
	* \brief Ordonne le chargement la configuration du jeu depuis plusieurs fichiers.
	* \return true en cas de succ�s, false sinon.
	*/
	bool chargement();

	/**
	* \brief Charge la configuration du jeu depuis un fichier.
	* \param nomFichier nom du fichier contenant la configuration � charger.
	* \return true en cas de succ�s, false sinon.
	*/
	bool chargementFichier (string nomFichier);


public:
	/**
	* \brief Force l'existance unique d'un objet configuration.
	* \details La premi�re fois que la m�thode est appel�e, une instance de la classe est cr�e. Les fois suivantes, seul le pointeur vers la premi�re instance est appel�e
	* 			et aucune autre instance n'est cr��e.
	* \return Le pointeur vers l'unique instance de type Configuration.
	*/
	static Configuration* getInstance();

	/**
	* \brief Lib�re la m�moire allou�e � l'unique instance de la classe Configuration.
	*/
	static Configuration* destruction();

	/**
	* \brief R�cup�re la valeur stock�e dans le conteneur map.
	* \param nomParametre Nom du param�tre � rechercher.
	* \return La valeur du param�tre sous forme de chaine.
	*/
	string getValeurParametre(const char* nomParametre);

#if 0
	int deleteEntry (char* nameEntry, string fichier_config);
#endif
};

