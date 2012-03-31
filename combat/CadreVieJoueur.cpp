#include "CadreVieJoueur.h"





// ------------------------------------------------------------------------------------
// ----------------------BOUTON vieJoueur------------------------------------------------
// ------------------------------------------------------------------------------------
CadreVieJoueur::CadreVieJoueur()
{
	debug->print("Constructeur vieJoueur appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();
	init();
	load();
}

bool CadreVieJoueur::init()
{
	typeBouttons=BOUTTONS_APTITUDE_PERSONNAGE;
    string boutonVieJoueurPosX=configuration->getValeurParametre("BoutonVieJoueur.posX");
    string boutonVieJoueurPosY=configuration->getValeurParametre("BoutonVieJoueur.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonVieJoueurPosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonVieJoueurPosY)*application->resolution.second));
	return true;
}

bool CadreVieJoueur::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	//animation=application->surfaces->getAnimation("BoutonSupport");
	pair<int, int> taille=surfaces->getSizeAnimationFirstImage("BoutonVieJoueur");
	int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation("BoutonVieJoueur", largeur, hauteur);
	imageCourante=(*animation).begin();

	viePerdue=(surfaces->getAnimation("ViePerdue")->at(0));
	int cur = 100;
	int max = 100;

	setVie(cur,max);

	return true;
}

bool CadreVieJoueur::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	dessineSurface(posXViePerdue, posYViePerdue, screen, viePerdue);

	return true;
}

bool CadreVieJoueur::action()
{
	return false;
}


void CadreVieJoueur::setVie(int& valeur, int& max)
{
	int largeur = (*imageCourante)->w - (*imageCourante)->w* valeur/max ;
	int hauteur = (*imageCourante)->h;
	viePerdue = redimensionneSurface(viePerdue,largeur,hauteur,false);

	posXViePerdue=posX+(*imageCourante)->w - largeur;
	posYViePerdue=posY;
}