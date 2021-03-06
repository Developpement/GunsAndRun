#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include "definitions.h"
#include "Debug.h"
#ifdef WIN32
#include <Les miens/DialogueTr.h>
#include <windows.h>
#endif
using namespace std;

/**
* \class ConfigurationJeu
* \brief Stocke et fournit un acc�s � la configuration du jeu.
*/
class ConfigurationJeu
{
	/*! La configuration du jeu: <le nom ou r�f�rence, la config ou valeur> */
	map<string,string> config;
	/*! Unique instance de la configuration du jeu. */
	static ConfigurationJeu* _singleton;

	Debug* debug;

	/**
	* \brief Constructeur de la classe ConfigurationJeu.
	*/
	ConfigurationJeu();

	/**
	* \brief Ordonne le chargement la configuration du jeu depuis plusieurs fichiers.
	* \return true en cas de succ�s, false sinon.
	*/
	bool chargement();

public:
	/**
	* \brief Charge la configuration du jeu depuis un fichier.
	* \param nomFichier nom du fichier contenant la configuration � charger.
	* \return true en cas de succ�s, false sinon.
	*/
	bool chargementFichier (string nomFichier);

	/**
	* \brief Force l'existance unique d'un objet configuration.
	* \details La premi�re fois que la m�thode est appel�e, une instance de la classe est cr�e. Les fois suivantes, seul le pointeur vers la premi�re instance est appel�e
	* 			et aucune autre instance n'est cr��e.
	* \return Le pointeur vers l'unique instance de type ConfigurationJeu.
	*/
	static ConfigurationJeu* getInstance();

	/**
	* \brief Lib�re la m�moire allou�e � l'unique instance de la classe ConfigurationJeu.
	*/
	static ConfigurationJeu* destruction();

	/**
	* \brief R�cup�re la valeur stock�e dans le conteneur map.
	* \param nomParametre Nom du param�tre � rechercher.
	* \return La valeur du param�tre sous forme de chaine.
	*/
	//template <typename T>
	//T getValeurParametreA (const char* nomParametre);

	string getValeurParametre(const char* nomParametre, bool ask=true);

#if 0
	int deleteEntry (char* nameEntry, string fichier_config);
#endif
};

