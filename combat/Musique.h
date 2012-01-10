#pragma once

/*
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "ConfigurationJeu.h"
#include "definitions.h"
#include "Conversions.h"

#ifdef WIN32
#include <windows.h>
#endif

#include <map>
#include <string>
using namespace std;

**
* \struct MusiqueType
* \brief Enum�re tous les types de musique disponibles.
*
enum MusiqueType
{
	AMBIANT,
	CALME,
	VIF
};


**
* \class Musique
* \brief Permet de jouer de la musique ou des sons.
*
class Musique
{
	static Musique* _singleton;

	string repertoireSon, repertoireMusiqueAmbiant, repertoireMusiqueVif, repertoireMusiqueCalme;

	ConfigurationJeu* configuration;

	map<string, Mix_Music*>::iterator it_musiquesAmbiant;
	map<string, Mix_Music*>::iterator it_musiquesVif;
	map<string, Mix_Music*>::iterator it_musiquesCalme;

	map<string, Mix_Chunk*> sons;
	map<string, Mix_Music*> musiquesAmbiant;
	map<string, Mix_Music*> musiquesVif;
	map<string, Mix_Music*> musiquesCalme;

	Musique();
	~Musique();

	bool init();
	bool load();

public:
	static Musique* getInstance();
	static Musique* destruction();

	bool playMusique(MusiqueType);
	bool playSound(Mix_Chunk*);

};

*/
