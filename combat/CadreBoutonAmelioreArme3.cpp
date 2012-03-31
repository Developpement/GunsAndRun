#include "CadreBoutonAmelioreArme3.h"




// ------------------------------------------------------------------------------------
// ----------------------BOUTON AMELIORE ARME 3----------------------------------------
// ------------------------------------------------------------------------------------
BoutonAmelioreArme3::BoutonAmelioreArme3()
{
	debug->print("Constructeur BoutonAmelioreArme3 appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();
	init();
	load();
}

bool BoutonAmelioreArme3::init()
{
	typeBouttons=BOUTTONS_MODIFICATIONS_ARME;
   string boutonAmelioreArme3PosX=configuration->getValeurParametre("BoutonAmelioreArme3.posX");
   string boutonAmelioreArme3PosY=configuration->getValeurParametre("BoutonAmelioreArme3.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonAmelioreArme3PosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonAmelioreArme3PosY)*application->resolution.second));
	return true;
}

bool BoutonAmelioreArme3::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	animation=surfaces->getAnimation("BoutonAmelioreArme1");
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonAmelioreArme3::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	return true;
}

bool BoutonAmelioreArme3::action()
{
	return false;
}
