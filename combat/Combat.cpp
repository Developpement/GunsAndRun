#include "Gestionnaire.h"
#include <windows.h>

using namespace std;


int main( int argc, char* argv[] )
{
#ifdef WIN32
	char szthis[300];
	char* c = szthis + GetModuleFileName(0, szthis, 300);
	while(*c != '\\')
        c--;
    *c = 0;
	if(SetCurrentDirectory(szthis)==0)
        return -1;
#endif

	// Initialisation des objets static*
	Debug::getInstance();
	ConfigurationJeu::getInstance();
#ifndef NOMUSIC
	Musique::getInstance();
#endif

	// Lancement du jeu...
	Gestionnaire* application=Gestionnaire::getInstance();
	application->init();
	application->update();

	// Vide la m�moire pour les objets static*
	UsineBalles::destruction();
	UsineArmes::destruction();

	Surfaces::destruction();
	Gestionnaire::destruction();
//	Musique::destruction();
	ConfigurationJeu::destruction();
	Debug::destruct();

	return 0;
}
