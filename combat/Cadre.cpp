#include "Cadre.h"




Cadre::Cadre(int &posX, int &posY, Configuration *config, Surfaces *surfaces, Application* application)
{
	this->posX=posX;
	this->posY=posY;

	this->configuration=config;
	this->surfaces = surfaces;
	this->application = application;
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
	cout << "Cadre doit effectuer une action" << endl;

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