
#include "Musique.h"
/*
Musique* Musique::_singleton=0;


Musique::Musique ()
{
	this->configuration = ConfigurationJeu::getInstance();
	debug->print("Musique constructeur" << endl;
}

Musique* Musique::getInstance()
{
	if(_singleton==0) {
		_singleton=new Musique();
		if((_singleton->init()==false)||(_singleton->load()==false)){
			destruction();
		}
	}
	return _singleton;
}

Musique* Musique::destruction()
{
	delete _singleton;
	_singleton=0;
	return _singleton;
}



bool Musique::init()
{
#ifndef NOMUSIC
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
        return false;


#endif
	return true;
}


bool Musique::load()
{
#ifndef NOMUSIC
	// Chargement des sons et musiques dans les maps
	repertoireSon = configuration->getValeurParametre("repertoireSon");
	repertoireMusiqueAmbiant = configuration->getValeurParametre("repertoireMusiqueAmbiant");
	repertoireMusiqueVif = configuration->getValeurParametre("repertoireMusiqueVif");
	repertoireMusiqueCalme = configuration->getValeurParametre("repertoireMusiqueCalme");

	HANDLE hfind;
	WIN32_FIND_DATA wfd;
	string tofind;

	//Chargement de la musique 'ambiant'
	tofind = repertoireMusiqueAmbiant+"\\*.wav";
	hfind = FindFirstFile(tofind.c_str(), &wfd);
	if (hfind != INVALID_HANDLE_VALUE) {
		do {
			// the name of the oldest file must not be the current log file
			string cFileName(wfd.cFileName); // Get a wstring to work
			debug->print("Musique ambiant: " << cFileName << endl;
			Mix_Music* buf=Mix_LoadMUS((repertoireMusiqueAmbiant+"\\"+cFileName).c_str());
			if(buf!=NULL)
				musiquesAmbiant.insert(pair<string,Mix_Music*>(cFileName, buf) );

		}while (FindNextFile(hfind, &wfd));
	}
	else debug->print("Aucun fichier trouve dans le repertoire " << repertoireMusiqueAmbiant << endl;
	FindClose(hfind);

	// Chargement de la musique 'vif'
	tofind = repertoireMusiqueVif+"\\*.wav";
	hfind = FindFirstFile(tofind.c_str(), &wfd);
	if (hfind != INVALID_HANDLE_VALUE) {
		do {
			// the name of the oldest file must not be the current log file
			string cFileName(wfd.cFileName); // Get a wstring to work
			debug->print("Musique vif: " << cFileName << endl;
			Mix_Music* buf=Mix_LoadMUS((repertoireMusiqueVif+"\\"+cFileName).c_str());
			if(buf!=NULL)
				musiquesVif.insert(pair<string,Mix_Music*>(cFileName, buf) );

		}while (FindNextFile(hfind, &wfd));
	}
	else debug->print("Aucun fichier trouve dans le repertoire " << repertoireMusiqueVif << endl;
	FindClose(hfind);


	// Chargement de la musique 'calme'
	tofind = repertoireMusiqueCalme+"\\*.wav";
	hfind = FindFirstFile(tofind.c_str(), &wfd);
	if (hfind != INVALID_HANDLE_VALUE) {
		do {
			// the name of the oldest file must not be the current log file
			string cFileName(wfd.cFileName); // Get a wstring to work
			debug->print("Musique calme: " << cFileName << endl;
			Mix_Music* buf=Mix_LoadMUS((repertoireMusiqueCalme+"\\"+cFileName).c_str());
			if(buf!=NULL)
				musiquesCalme.insert(pair<string,Mix_Music*>(cFileName, buf) );

		}while (FindNextFile(hfind, &wfd));
	}
	else debug->print("Aucun fichier trouve dans le repertoire " << repertoireMusiqueCalme << endl;
	FindClose(hfind);

	// Chargement des sons
	tofind = repertoireSon+"\\*.wav";
	hfind = FindFirstFile(tofind.c_str(), &wfd);
	if (hfind != INVALID_HANDLE_VALUE) {
		do {
			// the name of the oldest file must not be the current log file
			string cFileName(wfd.cFileName); // Get a wstring to work
			debug->print("son trouve: " << cFileName << endl;
			Mix_Chunk* buf=Mix_LoadWAV((repertoireSon+"\\"+cFileName).c_str());
			if(buf!=NULL)
				sons.insert(pair<string,Mix_Chunk*>(cFileName, buf) );

		}while (FindNextFile(hfind, &wfd));
	}
	else debug->print("Aucun fichier trouve dans le repertoire " << repertoireSon << endl;
	FindClose(hfind);


	it_musiquesAmbiant = musiquesAmbiant.begin();
	it_musiquesVif = musiquesVif.begin();
	it_musiquesCalme = musiquesCalme.begin();
#endif
	return true;
}




Musique::~Musique()
{
	//Mix_FreeChunk
	//Mix_FreeMusic
	//Mix_CloseAudio();
}




bool Musique::playMusique(MusiqueType mus)
{
#ifndef NOMUSIC
	if( Mix_PlayingMusic() == 0 ) { // pas de musique en cours
		//On lance la musique
		if( Mix_PlayMusic( it_musiquesAmbiant->second, -1 ) == -1 ){
			it_musiquesAmbiant++;
			return false;
		}
		it_musiquesAmbiant++;
	}
#endif
	return true;
}


bool Musique::playSound(Mix_Chunk* snd)
{

	return false;
}
*/
