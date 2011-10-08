#include "Application.h"
#include <windows.h>

Application* Application::_singleton=0;

Application* Application::getInstance()  
{
	if(_singleton==0) {
		_singleton=new Application();
	}
	return _singleton;
}


Application* Application::destruction()
{
	delete _singleton;
	_singleton=0;
	return _singleton;
}



Application::Application()
{
	configuration=Configuration::getInstance();
	musique=Musique::getInstance();

	idCpt=0;
	cout << "Application constructeur" << endl;
}

Application::~Application()
{
	//TODO Suppression des donn�es en m�moire propres � l'application.
	// Les unit�es:
	for(list<Unite*>::iterator it=unitees.begin();it!=unitees.end();it++) {
		delete *it;
		*it=0;
	}
	unitees.clear();

	// Les balles:
	for(list<Balle*>::iterator it=balles.begin();it!=balles.end();it++) {
		delete *it;
		*it=0;
	}
	balles.clear();

	// Le cadre et le background (appel de destruction).



	/* free the background surface */
	SDL_FreeSurface(screen);
	/* cleanup SDL */
	SDL_Quit();
}


int Application::init ()
{
	/* initialize SDL */
	SDL_Init(SDL_INIT_EVERYTHING);

	/* set the title bar */
	string applicationTitre = configuration->getValeurParametre("ApplicationTitle");
	SDL_WM_SetCaption(applicationTitre.c_str(), applicationTitre.c_str());

	/* create window */
	string windowWidthStr= configuration->getValeurParametre("ScreenWidth");
	string windowHeightStr= configuration->getValeurParametre("ScreenHeight");
	windowWidth=stringToInt(windowWidthStr);
	windowHeight=stringToInt(windowHeightStr);
	int bytePerPixel = stringToInt(configuration->getValeurParametre("bytePerPixel"));
	bool isFullScreen = configuration->getValeurParametre("fullscreenEnable").compare("1")==0?true:false;
	if (isFullScreen)
		screen = SDL_SetVideoMode(windowWidth, windowHeight, bytePerPixel, SDL_FULLSCREEN | SDL_HWSURFACE);
	else {
		screen = SDL_SetVideoMode(windowWidth, windowHeight, bytePerPixel, SDL_HWSURFACE);
	}

	// Chargement des animations
	surfaces=Surfaces::getInstance();
	pair<int, int> tailleSurfaceBase = surfaces->getSizeAnimationFirstImage("cadreVisible");
	resolution.first = (float)(windowWidth)/tailleSurfaceBase.first;
	resolution.second = (float)(windowHeight)/tailleSurfaceBase.second;

	// cadre init
	int posXCadre=0;
	int posYCadre=0;
	// Background init
	int posXbackground = 0;
	int posYbackground = 0;
	cadre=new Cadre(posXCadre,posYCadre,configuration,surfaces,this);
	background = new Background(posXbackground,posYbackground, configuration, surfaces, this);


#ifndef NOUNIT
	int moiX = (windowWidth)/2;
	int moiY = (windowHeight)/2;

	unitees.push_back(new UniteJoueurJouable(moiX,moiY, string("armeDefaut"), string("BalleDefaut")));
	int newX = 100;
	int newY=newX;
	unitees.push_back(new UniteNonJoueur(newX, newY, string("armeDefaut"), string("BalleDefaut")));
#endif


	return 0;
}




int Application::update () 
{
	musique->playMusique(AMBIANT);



	int gameover = 0;
	/* message pump */
	while (!gameover)
	{
		/* look for an event */
		if (SDL_PollEvent(&event)) {
			
			switch (event.type) {
				case SDL_KEYDOWN:
					switch( event.key.keysym.sym ) {
						case SDLK_UP:	
							cout << "Touche haut appuyee" << endl;
							keyValue.isArrowUpPressed=true;		
							background->setSpeedKeyUpPressed();							
							break;
						case SDLK_DOWN:	
							cout << "Touche bas appuyee" << endl;
							keyValue.isArrowDownPressed=true;	
							background->setSpeedKeyDownPressed();
							break;
						case SDLK_LEFT:	
							cout << "Touche gauche appuyee" << endl;
							keyValue.isArrowLeftPressed=true;	
							background->setSpeedKeyLeftPressed();
							break;
						case SDLK_RIGHT:
							cout << "Touche droite appuyee" << endl;
							keyValue.isArrowRightPressed=true;	
							background->setSpeedKeyRightPressed();
							break;
						case SDLK_ESCAPE:	gameover = 1;	break;
						default: break;
					}
					break;

				//Si une touche a ete relachee
				case SDL_KEYUP:
					switch( event.key.keysym.sym )
					{
						case SDLK_UP:	
							cout << "Touche haut relache" << endl;
							keyValue.isArrowUpPressed=false;	
							background->setSpeedKeyUpReleased();
							break;
						case SDLK_DOWN:	
							cout << "Touche bas relache" << endl;
							keyValue.isArrowDownPressed=false;	
							background->setSpeedKeyDownReleased();
							break;
						case SDLK_LEFT:	
							cout << "Touche gauche relache" << endl;
							keyValue.isArrowLeftPressed=false;	
							background->setSpeedKeyLeftReleased();
							break;
						case SDLK_RIGHT:
							cout << "Touche droite relache" << endl;
							keyValue.isArrowRightPressed=false;	
							background->setSpeedKeyRightReleased();
							break;
						default: break;
					}
					break;
				//on veut r�cup�rer les positions de la souris lors d'un clic et d�terminer s'il s'agit d'une action sur le menu ou sur le terrain (Tir)
				//Le clic ne sera effectif que lorsque l'on aura relach� le bouton.
				case SDL_MOUSEBUTTONDOWN:
				{
					int x = event.motion.x;
					int y = event.motion.y;
					if(cadre->actionSouris(x,y)){
						cout << "Clic sur le cadre"<<endl;
						keyValue.isLeftMouseClickOnCadre=true;
						keyValue.isLeftMouseClickOnBackground=false;
					}
					else {
						cout << "Clic sur le terrain" << endl;
						keyValue.isLeftMouseClickOnCadre=false;
						keyValue.isLeftMouseClickOnBackground=true;
					}
				}
					break;
				case SDL_MOUSEBUTTONUP:

					if(keyValue.isLeftMouseClickOnCadre)
						cadre->handleInput(event);
					
					cout << "Bouton souris relache" <<endl;
					keyValue.isLeftMouseClickOnCadre=false;
					keyValue.isLeftMouseClickOnBackground=false;

					break;
				default: break;
			}// end switch

			for (list<Unite*>::iterator itUnite = unitees.begin(); itUnite != unitees.end(); itUnite++) {
				// controle sp�cifique au joueur, soit une unit�->traitement par l'objet
				if((*itUnite)->typeUnite==PJOUEUR_JOUABLE) {
					(*itUnite)->handleInput(event);
					break;
				}
			}

		}// end SDL_PollEvent

		//----------------------
		// UPDATING ROUTINE
		//----------------------
		background->update();

		list<Unite*>::iterator itUnite;
		for (itUnite = unitees.begin(); itUnite != unitees.end(); itUnite++) {
			(*itUnite)->update();
		}

		list<Balle*>::iterator itBalle;
		for (itBalle = balles.begin(); itBalle != balles.end(); itBalle++) {
			(*itBalle)->update();
		}

		// destruction des objets
		itBalle=balles.begin();
		while(itBalle!=balles.end()){
			if((*itBalle)->vie<=0) {
				delete (*itBalle);
				itBalle=balles.erase(itBalle);
			}
			else itBalle++;
		}
		itUnite=unitees.begin();
		while(itUnite!=unitees.end()){
			if((*itUnite)->vie<=0)
				itUnite=unitees.erase(itUnite);
			else itUnite++;
		}

		draw();
	} // end while 



	return 0;
}


/**
*/
int Application::draw() 
{
	background->draw(screen);

	list<Balle*>::iterator itBalle;
	for (itBalle = balles.begin(); itBalle != balles.end(); itBalle++) {
		(*itBalle)->draw(screen);
	}

	list<Unite*>::iterator itUnite;
	for (itUnite = unitees.begin(); itUnite != unitees.end(); itUnite++) {
		(*itUnite)->draw(screen);
	}

	cadre->draw(screen);

	/* update the screen */
	SDL_UpdateRect(screen, 0, 0, 0, 0);

	return 0;
}
