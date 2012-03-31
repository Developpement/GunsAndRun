#include "CadreBoutonVie.h"



// ------------------------------------------------------------------------------------
// ----------------------BOUTON VIE----------------------------------------------------
// ------------------------------------------------------------------------------------
CadreBoutonVie::CadreBoutonVie()
{
	debug->print("Constructeur CadreBoutonVie appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();
	init();
	load();
}

bool CadreBoutonVie::init()
{
	typeBouttons=BOUTTONS_APTITUDE_PERSONNAGE;
   string boutonViePosX=configuration->getValeurParametre("BoutonVie.posX");
   string boutonViePosY=configuration->getValeurParametre("BoutonVie.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonViePosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonViePosY)*application->resolution.second));
	return true;
}

bool CadreBoutonVie::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	//animation=surfaces->getAnimation("BoutonVie");
	pair<int, int> taille=surfaces->getSizeAnimationFirstImage("BoutonVie");
	int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation("BoutonVie", largeur, hauteur);
	imageCourante=(*animation).begin();
	return true;
}

bool CadreBoutonVie::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	return true;
}

bool CadreBoutonVie::action()
{
	return false;
}