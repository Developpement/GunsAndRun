#include "CadreBoutonAmelioreArme4.h"



// ------------------------------------------------------------------------------------
// ----------------------BOUTON AMELIORE ARME 4----------------------------------------
// ------------------------------------------------------------------------------------
BoutonAmelioreArme4::BoutonAmelioreArme4()
{
	debug->print("Constructeur BoutonAmelioreArme4 appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();
	init();
	load();
}

bool BoutonAmelioreArme4::init()
{
	typeBouttons=BOUTTONS_MODIFICATIONS_ARME;
   string boutonAmelioreArme4PosX=configuration->getValeurParametre("BoutonAmelioreArme4.posX");
   string boutonAmelioreArme4PosY=configuration->getValeurParametre("BoutonAmelioreArme4.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonAmelioreArme4PosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonAmelioreArme4PosY)*application->resolution.second));
	return true;
}

bool BoutonAmelioreArme4::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	animation=surfaces->getAnimation("BoutonAmelioreArme1");
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonAmelioreArme4::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	return true;
}

bool BoutonAmelioreArme4::action()
{
	return false;
}