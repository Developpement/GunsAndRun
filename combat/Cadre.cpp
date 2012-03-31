#include "Cadre.h"

// ----------------- relatifs au cadre ------------------------
#include "CadreBoutonAmelioreArme1.h"
#include "CadreBoutonAmelioreArme2.h"
#include "CadreBoutonAmelioreArme3.h"
#include "CadreBoutonAmelioreArme4.h"
#include "CadreBoutonArme1.h"
#include "CadreBoutonArme2.h"
#include "CadreBoutonArme3.h"
#include "CadreBoutonArme4.h"
#include "CadreBoutonDefense.h"
#include "CadreBoutonGrade.h"
#include "CadreBoutonMenu.h"
#include "CadreBoutonSupport.h"
#include "CadreBoutonSupprimeArme1.h"
#include "CadreBoutonSupprimeArme2.h"
#include "CadreBoutonSupprimeArme3.h"
#include "CadreBoutonSupprimeArme4.h"
#include "CadreBoutonVie.h"
#include "CadreCoffre.h"
#include "CadreVieJoueur.h"
#include "CadreCoffre.h"
// --------------------------------------------------------------



Cadre* Cadre::_singleton = 0;

Cadre* Cadre::getInstance()
{	
	if(_singleton==0)
		_singleton = new Cadre;
	return _singleton;
}

Cadre* Cadre::destruction()
{
	if(_singleton!=0) {
		delete _singleton;
		_singleton=0;
	}
	return _singleton;
}
	  
Cadre::Cadre()
{
	debug=Debug::getInstance();

	posX=posY=0;

	configuration=ConfigurationJeu::getInstance();
	surfaces = Surfaces::getInstance();
	application = Gestionnaire::getInstance();
	load();

	composantsCadre.push_back(new CadreCoffre());
	composantsCadre.push_back(new CadreVieJoueur());

	composantsCadre.push_back(new BoutonArme1());
	composantsCadre.push_back(new BoutonArme2());
	composantsCadre.push_back(new BoutonArme3());
	composantsCadre.push_back(new BoutonArme4());

	composantsCadre.push_back(new BoutonAmelioreArme1());
	composantsCadre.push_back(new BoutonAmelioreArme2());
	composantsCadre.push_back(new BoutonAmelioreArme3());
	composantsCadre.push_back(new BoutonAmelioreArme4());

	composantsCadre.push_back(new BoutonSupprimeArme1());
	composantsCadre.push_back(new BoutonSupprimeArme2());
	composantsCadre.push_back(new BoutonSupprimeArme3());
	composantsCadre.push_back(new BoutonSupprimeArme4());

	composantsCadre.push_back(new BoutonGrade());
	composantsCadre.push_back(new CadreBoutonVie());
	composantsCadre.push_back(new BoutonDefense());
	composantsCadre.push_back(new BoutonSupport());

	composantsCadre.push_back(new BoutonMenu());

	doitEffectuerUneAction=false;
}

Cadre::~Cadre()
{
	debug->print("Cadre destructeur appele");
}


int Cadre::load()
{
	animation=surfaces->getAnimation("cadreVisible",application->windowWidth, application->windowHeight);
	imageCourante=(*animation).begin();
	boitesCollisions=surfaces->getBoitesCollisions("cadreVisible", application->windowWidth, application->windowHeight);
	return 0;
}


/*
 * \brief Permet de savoir si le clic souris a été fait sur ce cadre (this)
 */
bool Cadre::actionSouris(int& X, int& Y)
{
	return collision(X,Y,posX,posY,*boitesCollisions);
}


int Cadre::selectionBouton(Uint16& X, Uint16& Y)
{
	debug->print("Cadre doit effectuer une action");
	for (vector<ComposantCadre*>::iterator it=composantsCadre.begin();it!=composantsCadre.end();it++){
		if((*it)->estClique(X,Y)==true)
			break;
	}
	return 0;
}


int Cadre::draw(SDL_Surface* screen) 
{
	dessineSurface(static_cast<int>(posX), static_cast<int>(posY), screen, (*imageCourante));

	for(vector<ComposantCadre*>::iterator it=composantsCadre.begin(); it!=composantsCadre.end();it++){
		(*it)->draw(screen);
	}
	return 0;
}

bool Cadre::changeImageBouttonArme (string& nom)
{
	for (vector<ComposantCadre*>::iterator it=composantsCadre.begin();it!=composantsCadre.end();it++){
		if((*it)->typeBouttons==BOUTTONS_SELECTION_ARME) {
			if((*it)->type.compare("boutonNoWeapon")==0){
				(*it)->changeImage(nom);
				return true;
			}
		}
	}
	return false;
}