#pragma once

#include "SDL.h"
#include "SDL_mixer.h"
#include "Configuration.h"
#include "definitions.h"
#include "Conversions.h"

#include <windows.h>


#include <map>
#include <string>
using namespace std;

/**
* \struct MusiqueType
* \brief Enumère tous les types de musique disponibles.
*/
enum MusiqueType 
{
	AMBIANT,
	CALME,
	VIF
};


/**
* \class Musique
* \brief Permet de jouer de la musique ou des sons.
*/
class Musique 
{
	static Musique* _singleton;

	string repertoireSon, repertoireMusiqueAmbiant, repertoireMusiqueVif, repertoireMusiqueCalme;

	Configuration* configuration;

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
