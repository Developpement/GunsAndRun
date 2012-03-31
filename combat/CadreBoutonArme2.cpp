#include "CadreBoutonArme2.h"


// ------------------------------------------------------------------------------------
// ----------------------BOUTON ARME 2-------------------------------------------------
// ------------------------------------------------------------------------------------
BoutonArme2::BoutonArme2()
{
	debug->print("Constructeur BoutonArme2 appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();
	init();
	load();
}

bool BoutonArme2::init()
{
	typeBouttons=BOUTTONS_SELECTION_ARME;
   string boutonArme2PosX=configuration->getValeurParametre("boutonArme2.posX");
   string boutonArme2PosY=configuration->getValeurParametre("boutonArme2.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonArme2PosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonArme2PosY)*application->resolution.second));
	return true;
}

bool BoutonArme2::load()
{
	type="boutonNoWeapon";
	Surfaces* surfaces=Surfaces::getInstance();
	//pair<int, int> taille=surfaces->getSizeAnimationFirstImage("boutonNoWeapon");
	//int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	//int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation(type.c_str());//, largeur, hauteur);
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonArme2::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	return true;
}

bool BoutonArme2::action()
{
	return false;
}
