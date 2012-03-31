#include "CadreBoutonSupprimeArme3.h"



// ------------------------------------------------------------------------------------
// ----------------------BOUTON SUPPRIME ARME 3----------------------------------------
// ------------------------------------------------------------------------------------
BoutonSupprimeArme3::BoutonSupprimeArme3()
{
	debug->print("Constructeur BoutonSupprimeArme3 appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();
	init();
	load();
}

bool BoutonSupprimeArme3::init()
{
	typeBouttons=BOUTTONS_MODIFICATIONS_ARME;
   string boutonSupprimeArme3PosX=configuration->getValeurParametre("BoutonSupprimeArme3.posX");
   string boutonSupprimeArme3PosY=configuration->getValeurParametre("BoutonSupprimeArme3.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonSupprimeArme3PosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonSupprimeArme3PosY)*application->resolution.second));
	return true;
}

bool BoutonSupprimeArme3::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	animation=surfaces->getAnimation("BoutonSupprimeArme1");
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonSupprimeArme3::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	return true;
}

bool BoutonSupprimeArme3::action()
{
	return false;
}