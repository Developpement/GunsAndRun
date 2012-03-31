#include "CadreBoutonAmelioreArme1.h"



// ------------------------------------------------------------------------------------
// ----------------------BOUTON AMELIORE ARME 1----------------------------------------
// ------------------------------------------------------------------------------------
BoutonAmelioreArme1::BoutonAmelioreArme1()
{
	debug->print("Constructeur BoutonAmelioreArme1 appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();
	init();
	load();
}

bool BoutonAmelioreArme1::init()
{
	typeBouttons=BOUTTONS_MODIFICATIONS_ARME;
   string boutonAmelioreArme1PosX=configuration->getValeurParametre("BoutonAmelioreArme1.posX");
   string boutonAmelioreArme1PosY=configuration->getValeurParametre("BoutonAmelioreArme1.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonAmelioreArme1PosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonAmelioreArme1PosY)*application->resolution.second));
	return true;
}

bool BoutonAmelioreArme1::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	//animation=application->surfaces->getAnimation("BoutonAmelioreArme1");
	pair<int, int> taille=surfaces->getSizeAnimationFirstImage("BoutonAmelioreArme1");
	int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation("BoutonAmelioreArme1", largeur, hauteur);
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonAmelioreArme1::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	return true;
}

bool BoutonAmelioreArme1::action()
{
	return false;
}