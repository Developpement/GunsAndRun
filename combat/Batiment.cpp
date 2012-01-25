#include "Batiment.h"


Batiment::Batiment()
{
	debug=Debug::getInstance();
	debug->print("Constructeur Batiment appele");
}

// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------Batiment------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
Marche::Marche(int posX, int posY)
{
#ifndef NOBUILDING
	application=Gestionnaire::getInstance();
	configuration=ConfigurationJeu::getInstance();
	surfaces=Surfaces::getInstance();

	// On incrémente l'identifiant pour que toutes les unitées aient un identifiant différent.
	typeBatiment="Marche";

	animation=0;
	boitesCollisions=0;

	load();

	this->posX = static_cast<float>(posX - (*animation)[0]->w/2) + application->background->posXbackground;
	this->posY = static_cast<float>(posY - (*animation)[0]->h/2) + application->background->posYbackground;
#endif
}


int Marche::load()
{
#ifndef NOBUILDING
	// graphics
	animation = surfaces->getAnimation("Marche");
	imageUniteCourante=(*animation).begin();
	boitesCollisions = surfaces->getBoitesCollisions("Marche");

	//autres
	//vie = stringToInt(configuration->getValeurParametre("MarcheVie"));
#endif
	return 0;
}



int Marche::handleInput(SDL_Event& event)
{

	return 0;
}


int Marche::update()
{
#ifndef NOBUILDING
	velX=application->background->velXbackground;
	velY=application->background->velYbackground;
	posX += velX;
	posY += velY;
#endif
	return 0;
}

int Marche::draw(SDL_Surface* screen)
{
#ifndef NOBUILDING
	afficheEcran(static_cast<int>(posX), static_cast<int>(posY), screen, *imageUniteCourante);
#endif
	return 0;
}

