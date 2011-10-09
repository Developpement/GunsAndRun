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
* \brief Stocke et fournit un accès à la configuration du jeu.
*/
class Configuration
{
	/*! La configuration du jeu: <le nom ou référence, la config ou valeur> */
	map<string,string> config;
	/*! Unique instance de la configuration du jeu. */
	static Configuration* _singleton;

	/**
	* \brief Constructeur de la classe Configuration.
	*/
	Configuration();

	/**
	* \brief Ordonne le chargement la configuration du jeu depuis plusieurs fichiers.
	* \return true en cas de succès, false sinon.
	*/
	bool chargement();

	/**
	* \brief Charge la configuration du jeu depuis un fichier.
	* \param nomFichier nom du fichier contenant la configuration à charger.
	* \return true en cas de succès, false sinon.
	*/
	bool chargementFichier (string nomFichier);


public:
	/**
	* \brief Force l'existance unique d'un objet configuration.
	* \details La première fois que la méthode est appelée, une instance de la classe est crée. Les fois suivantes, seul le pointeur vers la première instance est appelée
	* 			et aucune autre instance n'est créée.
	* \return Le pointeur vers l'unique instance de type Configuration.
	*/
	static Configuration* getInstance();

	/**
	* \brief Libère la mémoire allouée à l'unique instance de la classe Configuration.
	*/
	static Configuration* destruction();

	/**
	* \brief Récupère la valeur stockée dans le conteneur map.
	* \param nomParametre Nom du paramètre à rechercher.
	* \return La valeur du paramètre sous forme de chaine.
	*/
	string getValeurParametre(const char* nomParametre);

#if 0
	int deleteEntry (char* nameEntry, string fichier_config);
#endif
};

