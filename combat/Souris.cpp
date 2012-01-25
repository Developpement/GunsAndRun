#include "Souris.h"



Souris* Souris::_singleton = 0;


Souris* Souris::getInstance()
{
	if(_singleton==0)
		_singleton=new Souris();
	return _singleton;
}

Souris* Souris::destruction()
{
	if(_singleton!=0) {
		delete _singleton;
		_singleton=0;
	}
	return _singleton;
}


Souris::Souris()
{
	debug=Debug::getInstance();
	//gestionnaire=Gestionnaire::getInstance();
	//cadre=Cadre::getInstance();

	isLeftMouseClickOnCadre=false;
	isLeftMouseClickOnBackground=false;
}


void Souris::handleInput(SDL_Event& event)
{
	switch (event.type) {
		
		case SDL_MOUSEMOTION:
		{
			Gestionnaire* gestionnaire=Gestionnaire::getInstance();
			for (list<Unite*>::iterator itUnite = gestionnaire->unitees.begin(); itUnite != gestionnaire->unitees.end(); itUnite++) {
			// controle spécifique au joueur, soit une unité->traitement par l'objet
				if((*itUnite)->typeUnite==PJOUEUR_JOUABLE) {
					(*itUnite)->handleInput(event);
					break;
				}
			}
		}
			break;

		//on veut récupérer les positions de la souris lors d'un clic et déterminer s'il s'agit d'une action sur le menu ou sur le terrain (Tir)
		//Le clic ne sera effectif que lorsque l'on aura relaché le bouton.
		case SDL_MOUSEBUTTONDOWN:
		{
			int x = event.motion.x;
			int y = event.motion.y;
			if(Cadre::getInstance()->actionSouris(x,y)){
				debug->print("Clic sur le cadre");
				isLeftMouseClickOnCadre=true;
				isLeftMouseClickOnBackground=false;
			}
			else {
				Gestionnaire* gestionnaire=Gestionnaire::getInstance();
				for (list<Unite*>::iterator itUnite = gestionnaire->unitees.begin(); itUnite != gestionnaire->unitees.end(); itUnite++) {
				// controle spécifique au joueur, soit une unité->traitement par l'objet
					if((*itUnite)->typeUnite==PJOUEUR_JOUABLE) {
						(*itUnite)->handleInput(event);
						break;
					}
				}
				debug->print("Clic sur le terrain");
				isLeftMouseClickOnCadre=false;
				isLeftMouseClickOnBackground=true;
			}
		}
			break;
		case SDL_MOUSEBUTTONUP:
			if(isLeftMouseClickOnCadre)
				Cadre::getInstance()->selectionBouton(event.motion.x, event.motion.y);
			else {
				Gestionnaire* gestionnaire=Gestionnaire::getInstance();
				for (list<Unite*>::iterator itUnite = gestionnaire->unitees.begin(); itUnite != gestionnaire->unitees.end(); itUnite++) {
				// controle spécifique au joueur, soit une unité->traitement par l'objet
					if((*itUnite)->typeUnite==PJOUEUR_JOUABLE) {
						(*itUnite)->handleInput(event);
						break;
					}
				}
			}

			debug->print("Bouton souris relache");
			isLeftMouseClickOnCadre=false;
			isLeftMouseClickOnBackground=false;

			break;
		default: break;
	}// end switch
}