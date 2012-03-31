#include "CadreBoutonAmelioreArme2.h"




// ------------------------------------------------------------------------------------
// ----------------------BOUTON AMELIORE ARME 2----------------------------------------
// ------------------------------------------------------------------------------------
BoutonAmelioreArme2::BoutonAmelioreArme2()
{
	debug->print("Constructeur BoutonAmelioreArme2 appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();
	init();
	load();
}

bool BoutonAmelioreArme2::init()
{
	typeBouttons=BOUTTONS_MODIFICATIONS_ARME;
   string boutonAmelioreArme2PosX=configuration->getValeurParametre("BoutonAmelioreArme2.posX");
   string boutonAmelioreArme2PosY=configuration->getValeurParametre("BoutonAmelioreArme2.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonAmelioreArme2PosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonAmelioreArme2PosY)*application->resolution.second));
	return true;
}

bool BoutonAmelioreArme2::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	animation=surfaces->getAnimation("BoutonAmelioreArme1");
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonAmelioreArme2::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	return true;
}

bool BoutonAmelioreArme2::action()
{
	return false;
}
