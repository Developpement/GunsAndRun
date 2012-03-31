#include "CadreBoutonSupport.h"



// ------------------------------------------------------------------------------------
// ----------------------BOUTON SUPPORT------------------------------------------------
// ------------------------------------------------------------------------------------
BoutonSupport::BoutonSupport()
{
	debug->print("Constructeur BoutonSupport appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();
	init();
	load();
}

bool BoutonSupport::init()
{
	typeBouttons=BOUTTONS_APTITUDE_PERSONNAGE;
   string boutonSupportPosX=configuration->getValeurParametre("BoutonSupport.posX");
   string boutonSupportPosY=configuration->getValeurParametre("BoutonSupport.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonSupportPosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonSupportPosY)*application->resolution.second));
	return true;
}

bool BoutonSupport::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	//animation=application->surfaces->getAnimation("BoutonSupport");
	pair<int, int> taille=surfaces->getSizeAnimationFirstImage("BoutonSupport");
	int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation("BoutonSupport", largeur, hauteur);
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonSupport::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	return true;
}

bool BoutonSupport::action()
{
	return false;
}
