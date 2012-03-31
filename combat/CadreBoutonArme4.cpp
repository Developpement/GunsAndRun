#include "CadreBoutonArme4.h"



// ------------------------------------------------------------------------------------
// ----------------------BOUTON ARME 4-------------------------------------------------
// ------------------------------------------------------------------------------------
BoutonArme4::BoutonArme4()
{
	debug->print("Constructeur BoutonArme4 appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();
	init();
	load();
}

bool BoutonArme4::init()
{
	typeBouttons=BOUTTONS_SELECTION_ARME;
   string boutonArme4PosX=configuration->getValeurParametre("boutonArme4.posX");
   string boutonArme4PosY=configuration->getValeurParametre("boutonArme4.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonArme4PosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonArme4PosY)*application->resolution.second));
	return true;
}

bool BoutonArme4::load()
{
	type="boutonNoWeapon";
	Surfaces* surfaces=Surfaces::getInstance();
	animation=surfaces->getAnimation(type.c_str());
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonArme4::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	return true;
}

bool BoutonArme4::action()
{
	return false;
}