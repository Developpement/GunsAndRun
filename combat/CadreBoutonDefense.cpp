#include "CadreBoutonDefense.h"




// ------------------------------------------------------------------------------------
// ----------------------BOUTON DEFENSE------------------------------------------------
// ------------------------------------------------------------------------------------
BoutonDefense::BoutonDefense()
{
	debug->print("Constructeur BoutonDefense appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();
	init();
	load();
}

bool BoutonDefense::init()
{
	typeBouttons=BOUTTONS_APTITUDE_PERSONNAGE;
   string boutonDefensePosX=configuration->getValeurParametre("BoutonDefense.posX");
   string boutonDefensePosY=configuration->getValeurParametre("BoutonDefense.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonDefensePosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonDefensePosY)*application->resolution.second));
	return true;
}

bool BoutonDefense::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	//animation=surfaces->getAnimation("BoutonDefense");
	pair<int, int> taille=surfaces->getSizeAnimationFirstImage("BoutonDefense");
	int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation("BoutonDefense", largeur, hauteur);
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonDefense::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	return true;
}

bool BoutonDefense::action()
{
	return false;
}