#include "Cadre.h"

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

	configuration=Configuration::getInstance();
	surfaces = Surfaces::getInstance();
	application = Application::getInstance();
	load();


	boutonsCadre.push_back(new BoutonArme1());
	boutonsCadre.push_back(new BoutonArme2());
	boutonsCadre.push_back(new BoutonArme3());
	boutonsCadre.push_back(new BoutonArme4());

	boutonsCadre.push_back(new BoutonAmelioreArme1());
	boutonsCadre.push_back(new BoutonAmelioreArme2());
	boutonsCadre.push_back(new BoutonAmelioreArme3());
	boutonsCadre.push_back(new BoutonAmelioreArme4());

	boutonsCadre.push_back(new BoutonSupprimeArme1());
	boutonsCadre.push_back(new BoutonSupprimeArme2());
	boutonsCadre.push_back(new BoutonSupprimeArme3());
	boutonsCadre.push_back(new BoutonSupprimeArme4());

	boutonsCadre.push_back(new BoutonGrade());
	boutonsCadre.push_back(new BoutonVie());
	boutonsCadre.push_back(new BoutonDefense());
	boutonsCadre.push_back(new BoutonSupport());

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
*\brief Permet de savoir si le clic souris a été fait sur ce cadre (this)
*/
bool Cadre::actionSouris(int& X, int& Y)
{
	return collision(X,Y,posX,posY,*boitesCollisions);
}


int Cadre::handleInput(SDL_Event& event)
{
	debug->print("Cadre doit effectuer une action");

	return 0;
}


int Cadre::draw(SDL_Surface* screen) 
{
	afficheEcran(static_cast<int>(posX), static_cast<int>(posY), screen, (*imageCourante));

	for(vector<Bouton*>::iterator it=boutonsCadre.begin(); it!=boutonsCadre.end();it++){
		(*it)->draw(screen);
	}
	return 0;
}

bool Cadre::changeImageBouttonArme (string& nom)
{
	for (vector<Bouton*>::iterator it=boutonsCadre.begin();it!=boutonsCadre.end();it++){
		if((*it)->typeBouttons==BOUTTONS_SELECTION_ARME) {
			if((*it)->type.compare("boutonNoWeapon")==0){
				(*it)->changeImage(nom);
				return true;
			}
		}
	}
	return false;
}