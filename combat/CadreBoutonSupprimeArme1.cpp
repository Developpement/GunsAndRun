#include "CadreBoutonSupprimeArme1.h"



// ------------------------------------------------------------------------------------
// ----------------------BOUTON SUPPRIME ARME 1----------------------------------------
// ------------------------------------------------------------------------------------
BoutonSupprimeArme1::BoutonSupprimeArme1()
{
	debug->print("Constructeur BoutonSupprimeArme1 appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();
	init();
	load();
}

bool BoutonSupprimeArme1::init()
{
	typeBouttons=BOUTTONS_MODIFICATIONS_ARME;
   string boutonSupprimeArme1PosX=configuration->getValeurParametre("BoutonSupprimeArme1.posX");
   string boutonSupprimeArme1PosY=configuration->getValeurParametre("BoutonSupprimeArme1.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonSupprimeArme1PosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonSupprimeArme1PosY)*application->resolution.second));
	return true;
}

bool BoutonSupprimeArme1::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	//animation=application->surfaces->getAnimation("BoutonSupprimeArme1");
	pair<int, int> taille=surfaces->getSizeAnimationFirstImage("BoutonSupprimeArme1");
	int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation("BoutonSupprimeArme1", largeur, hauteur);
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonSupprimeArme1::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	return true;
}

bool BoutonSupprimeArme1::action()
{
	return false;
}