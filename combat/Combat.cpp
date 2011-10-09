#include "Application.h"
#include <windows.h>

using namespace std;


int main( int argc, char* argv[] )
{
#ifdef WIN32
	char szthis[300];
	char* c = szthis + GetModuleFileName(0, szthis, 300);
	while(*c != '\\') c--; *c = 0;
	SetCurrentDirectory(szthis);
#endif

	// Initialisation des objets static*
	Configuration::getInstance();
	Musique::getInstance();

	// Lancement du jeu...
	Application* application=Application::getInstance();
	application->init();
	application->update();

	// Vide la mémoire pour les objets static*
	UsineBalles::destruction();
	UsineArmes::destruction();

	Surfaces::destruction();
	Application::destruction();
	Musique::destruction();
	Configuration::destruction();


	return 0;
}
