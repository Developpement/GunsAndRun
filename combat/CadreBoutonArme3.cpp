#include "CadreBoutonArme3.h"




// ------------------------------------------------------------------------------------
// ----------------------BOUTON ARME 3-------------------------------------------------
// ------------------------------------------------------------------------------------

BoutonArme3::BoutonArme3()
{
	debug->print("Constructeur BoutonArme3 appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();
	init();
	load();
}

bool BoutonArme3::init()
{
	typeBouttons=BOUTTONS_SELECTION_ARME;
   string boutonArme3PosX=configuration->getValeurParametre("boutonArme3.posX");
   string boutonArme3PosY=configuration->getValeurParametre("boutonArme3.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonArme3PosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonArme3PosY)*application->resolution.second));
	return true;
}

bool BoutonArme3::load()
{
	type="boutonNoWeapon";
	Surfaces* surfaces=Surfaces::getInstance();
	animation=surfaces->getAnimation(type.c_str());
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonArme3::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	return true;
}

bool BoutonArme3::action()
{
	return false;
}