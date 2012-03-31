#include "CadreBoutonSupprimeArme4.h"



// ------------------------------------------------------------------------------------
// ----------------------BOUTON SUPPRIME ARME 4----------------------------------------
// ------------------------------------------------------------------------------------
BoutonSupprimeArme4::BoutonSupprimeArme4()
{
	debug->print("Constructeur BoutonSupprimeArme4 appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();
	init();
	load();
}

bool BoutonSupprimeArme4::init()
{
	typeBouttons=BOUTTONS_MODIFICATIONS_ARME;
   string boutonSupprimeArme4PosX=configuration->getValeurParametre("BoutonSupprimeArme4.posX");
   string boutonSupprimeArme4PosY=configuration->getValeurParametre("BoutonSupprimeArme4.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonSupprimeArme4PosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonSupprimeArme4PosY)*application->resolution.second));
	return true;
}

bool BoutonSupprimeArme4::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	animation=surfaces->getAnimation("BoutonSupprimeArme1");
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonSupprimeArme4::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	return true;
}

bool BoutonSupprimeArme4::action()
{
	return false;
}