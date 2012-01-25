#include "Clavier.h"


Clavier* Clavier::_singleton = 0;




Clavier* Clavier::getInstance()
{
	if(_singleton==0)
		_singleton=new Clavier();
	return _singleton;
}

Clavier* Clavier::destruction()
{
	if(_singleton!=0) {
		delete _singleton;
		_singleton=0;
	}
	return _singleton;
}


Clavier::Clavier()
{
	debug=Debug::getInstance();
	//background=Background::getInstance();
	//isArrowUpPressed=false;
	//isArrowLeftPressed=false;
	//isArrowDownPressed=false;
	//isArrowRightPressed=false;
	etatClavier=AUCUNE_FLECHE_PRESSEE;
	//isLeftMouseClickOnCadre=false;
	//isLeftMouseClickOnBackground=false;
}



void Clavier::handleInput(SDL_Event& event)
{
	switch (event.type) {
		case SDL_KEYDOWN:
			switch( event.key.keysym.sym ) {
				case SDLK_UP:
					debug->print("Touche haut appuyee");
					etatClavier|=FLECHE_HAUT_PRESSEE;
					Background::getInstance()->setDirection();
					break;
				case SDLK_DOWN:
					debug->print("Touche bas appuyee");
					etatClavier|=FLECHE_BAS_PRESSEE;
					Background::getInstance()->setDirection();
					break;
				case SDLK_LEFT:
					debug->print("Touche gauche appuyee");
					etatClavier|=FLECHE_GAUCHE_PRESSEE;
					Background::getInstance()->setDirection();
					break;
				case SDLK_RIGHT:
					debug->print("Touche droite appuyee");
					etatClavier|=FLECHE_DROITE_PRESSEE;
					Background::getInstance()->setDirection();
					break;
				case SDLK_ESCAPE:
					Gestionnaire::getInstance()->close();
					break;
				default: 
					break;
			}
			break;

				//Si une touche a ete relachee
		case SDL_KEYUP:
			switch( event.key.keysym.sym )
			{
				case SDLK_UP:
					debug->print("Touche haut relache");
					etatClavier&=~FLECHE_HAUT_PRESSEE;
					Background::getInstance()->setDirection();
					break;
				case SDLK_DOWN:
					debug->print("Touche bas relache");
					etatClavier&=~FLECHE_BAS_PRESSEE;
					Background::getInstance()->setDirection();
					break;
				case SDLK_LEFT:
					debug->print("Touche gauche relache");
					etatClavier&=~FLECHE_GAUCHE_PRESSEE;
					Background::getInstance()->setDirection();
					break;
				case SDLK_RIGHT:
					debug->print("Touche droite relache");
					etatClavier&=~FLECHE_DROITE_PRESSEE;
					Background::getInstance()->setDirection();
					break;
				default: break;
			}
			break;
	}



}