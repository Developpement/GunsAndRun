#include "CadreCoffre.h"




// ------------------------------------------------------------------------------------
// ----------------------BOUTON COFFRE-------------------------------------------------
// ------------------------------------------------------------------------------------
CadreCoffre::CadreCoffre()
{
	debug->print("Constructeur Coffre appele!");
	this->application=Gestionnaire::getInstance();
	this->configuration=ConfigurationJeu::getInstance();

	init();
	load();
}

bool CadreCoffre::init()
{
	typeBouttons=BOUTONS_INACTIF;
	string boutonCoffrePosX=configuration->getValeurParametre("Coffre.posX");
	string boutonCoffrePosY=configuration->getValeurParametre("Coffre.posY");

	posX = static_cast<int>(ceil(stringToFloat(boutonCoffrePosX)*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(boutonCoffrePosY)*application->resolution.second));
	return true;
}

bool CadreCoffre::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	pair<int, int> taille=surfaces->getSizeAnimationFirstImage("Coffre");
	int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation("Coffre", largeur, hauteur);
	imageCourante=(*animation).begin();

	string argentStr = configuration->getValeurParametre("joueurJouable.StartMoney");
	valeur = stringToInt(argentStr);

	string message;
	unsigned int nbChar=5;
	if(argentStr.length()<nbChar) {
		//int nbEspaceDebut=ceil(
		message.append((unsigned int)ceil((double)(nbChar-argentStr.length())/2),' ');
		message+=argentStr;
		message.append(nbChar-message.length(),' ');
	}
	else message=" xxxxx ";
	
	int hauteurPolice = hauteur/3;
	argent = new Texte(CASLONBOLD, hauteurPolice, message, couleur_noir,largeur,hauteurPolice);

	posXArgent=posX;
	posYArgent=posY+hauteur-hauteurPolice;

	return true;
}

bool CadreCoffre::draw(SDL_Surface* screen)
{
	dessineSurface(posX, posY, screen, *imageCourante);
	dessineSurface(posXArgent, posYArgent, screen, (argent->getSurface()));
	return true;
}

bool CadreCoffre::action()
{
	return false;
}

