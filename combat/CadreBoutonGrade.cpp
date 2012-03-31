#include "CadreBoutonGrade.h"



// ------------------------------------------------------------------------------------
// ----------------------BOUTON GRADE--------------------------------------------------
// ------------------------------------------------------------------------------------
BoutonGrade::BoutonGrade()
{
	debug->print("Constructeur BoutonGrade appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();
	init();
	load();
}

bool BoutonGrade::init()
{
	typeBouttons=BOUTTONS_APTITUDE_PERSONNAGE;
    string boutonGradePosX=configuration->getValeurParametre("BoutonGrade.posX");
    string boutonGradePosY=configuration->getValeurParametre("BoutonGrade.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonGradePosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonGradePosY)*application->resolution.second));
	return true;
}

bool BoutonGrade::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	//animation=surfaces->getAnimation("BoutonGrade");
	pair<int, int> taille=surfaces->getSizeAnimationFirstImage("BoutonGrade");
	int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation("BoutonGrade", largeur, hauteur);
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonGrade::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	return true;
}

bool BoutonGrade::action()
{
	return false;
}