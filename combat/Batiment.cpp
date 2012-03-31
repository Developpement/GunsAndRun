#include "Batiment.h"


Batiment::Batiment()
{
	debug=Debug::getInstance();
	debug->print("Constructeur Batiment appele");
}

// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------Marche------------------------------------------------------------
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

	this->posX = static_cast<float>(posX /*- (*animation)[0]->w/2*/) + application->background->posXbackground;
	this->posY = static_cast<float>(posY /*- (*animation)[0]->h/2*/) + application->background->posYbackground;
#endif
}


int Marche::load()
{
#ifndef NOBUILDING
	// graphics
	animation = surfaces->getAnimation(typeBatiment.c_str());
	imageUniteCourante=(*animation).begin();
	boitesCollisions = surfaces->getBoitesCollisions(typeBatiment.c_str());

	//autres
	string batimentVieStr = typeBatiment + ".vie";
	vie = stringToInt(configuration->getValeurParametre(batimentVieStr.c_str()));
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
	dessineSurface(static_cast<int>(posX), static_cast<int>(posY), screen, *imageUniteCourante);
#endif
	return 0;
}

// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------QG------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
QG::QG(int posX, int posY)
{
#ifndef NOBUILDING
	application=Gestionnaire::getInstance();
	configuration=ConfigurationJeu::getInstance();
	surfaces=Surfaces::getInstance();

	// On incrémente l'identifiant pour que toutes les unitées aient un identifiant différent.
	typeBatiment="QG";

	animation=0;
	boitesCollisions=0;

	load();

	this->posX = static_cast<float>(posX /*- (*animation)[0]->w/2*/) + application->background->posXbackground;
	this->posY = static_cast<float>(posY /*- (*animation)[0]->h/2*/) + application->background->posYbackground;
#endif
}


int QG::load()
{
#ifndef NOBUILDING
	// graphics
	animation = surfaces->getAnimation("QG");
	imageUniteCourante=(*animation).begin();
	boitesCollisions = surfaces->getBoitesCollisions("QG");

	//autres
	string batimentVieStr = typeBatiment + ".vie";
	vie = stringToInt(configuration->getValeurParametre(batimentVieStr.c_str()));
#endif
	return 0;
}



int QG::handleInput(SDL_Event& event)
{

	return 0;
}


int QG::update()
{
#ifndef NOBUILDING
	velX=application->background->velXbackground;
	velY=application->background->velYbackground;
	posX += velX;
	posY += velY;
#endif
	return 0;
}

int QG::draw(SDL_Surface* screen)
{
#ifndef NOBUILDING
	dessineSurface(static_cast<int>(posX), static_cast<int>(posY), screen, *imageUniteCourante);
#endif
	return 0;
}