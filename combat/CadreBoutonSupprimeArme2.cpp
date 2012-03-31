#include "CadreBoutonSupprimeArme2.h"


// ------------------------------------------------------------------------------------
// ----------------------BOUTON SUPPRIME ARME 2----------------------------------------
// ------------------------------------------------------------------------------------
BoutonSupprimeArme2::BoutonSupprimeArme2()
{
	debug->print("Constructeur BoutonSupprimeArme2 appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();
	init();
	load();
}

bool BoutonSupprimeArme2::init()
{
	typeBouttons=BOUTTONS_MODIFICATIONS_ARME;
   string boutonSupprimeArme2PosX=configuration->getValeurParametre("BoutonSupprimeArme2.posX");
   string boutonSupprimeArme2PosY=configuration->getValeurParametre("BoutonSupprimeArme2.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonSupprimeArme2PosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonSupprimeArme2PosY)*application->resolution.second));
	return true;
}

bool BoutonSupprimeArme2::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	animation=surfaces->getAnimation("BoutonSupprimeArme1");
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonSupprimeArme2::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	return true;
}

bool BoutonSupprimeArme2::action()
{
	return false;
}