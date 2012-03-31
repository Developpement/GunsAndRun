#include "CadreBoutonMenu.h"
#include "Form_menu.h"


// ------------------------------------------------------------------------------------
// ----------------------BOUTON MENU---------------------------------------------------
// ------------------------------------------------------------------------------------
BoutonMenu::BoutonMenu()
{
	debug->print("Constructeur BoutonMenu appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();
	init();
	load();
}

bool BoutonMenu::init()
{
	typeBouttons=BOUTTONS_APTITUDE_PERSONNAGE;
   string boutonSupportPosX=configuration->getValeurParametre("BoutonMenu.posX");
   string boutonSupportPosY=configuration->getValeurParametre("BoutonMenu.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonSupportPosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonSupportPosY)*application->resolution.second));
	return true;
}

bool BoutonMenu::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	//animation=application->surfaces->getAnimation("BoutonSupport");
	pair<int, int> taille=surfaces->getSizeAnimationFirstImage("BoutonMenu");
	int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation("BoutonMenu", largeur, hauteur);
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonMenu::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	return true;
}

bool BoutonMenu::action()
{
	debug->print("BoutonMenu doit effecter une action!");
	combat::Form_menu formMenu;
	switch (formMenu.choixMenu)
	{
		case OPTIONS:
		case INSTRUCTIONS:
		case APROPOS:
		case RETOURJEU:
			break;
		case QUITTERJEU:
			application->close();
			break;
		case AUCUN:
		default:
			break;
	}
	return false;
}
