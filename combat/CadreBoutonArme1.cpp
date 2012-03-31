#include "CadreBoutonArme1.h"



// ------------------------------------------------------------------------------------
// ----------------------BOUTON ARME 1-------------------------------------------------
// ------------------------------------------------------------------------------------
BoutonArme1::BoutonArme1()
{
	debug->print("Constructeur BoutonArme1 appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();
	init();
	load();
}

bool BoutonArme1::init()
{
	typeBouttons=BOUTTONS_SELECTION_ARME;
   string boutonArme1PosX=configuration->getValeurParametre("boutonArme1.posX");
	string boutonArme1PosY=configuration->getValeurParametre("boutonArme1.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonArme1PosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonArme1PosY)*application->resolution.second));
	return true;
}

bool BoutonArme1::load()
{
	type="boutonNoWeapon";
	Surfaces* surfaces=Surfaces::getInstance();
	//animation=application->surfaces->getAnimation("boutonAucuneArme");
	pair<int, int> taille=surfaces->getSizeAnimationFirstImage("boutonNoWeapon");
	int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation(type.c_str(), largeur, hauteur);
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonArme1::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	return true;
}

bool BoutonArme1::action()
{
	return false;
}
