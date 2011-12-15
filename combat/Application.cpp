#include "Application.h"
#include <windows.h>

Application* Application::_singleton=0;

/**
* \brief
*/
Application* Application::getInstance()
{
	if(_singleton==0) {
		_singleton=new Application();
	}
	return _singleton;
}


/**
* \brief
*/
Application* Application::destruction()
{
	delete _singleton;
	_singleton=0;
	return _singleton;
}


/**
* \brief
*/
Application::Application()
{
	configuration=Configuration::getInstance();
	timers=Timers::getInstance();
//	musique=Musique::getInstance();
	debug=Debug::getInstance();

	idCpt=0;
	debug->print("Application constructeur");
}

/**
* \brief
*/
Application::~Application()
{
	//TODO Suppression des données en mémoire propres à l'application.
	// Les unitées:
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

/**
* \brief
*/
int Application::init ()
{
    const char bytePerPixelStr[]="bytePerPixel";
    string param;

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

    param=configuration->getValeurParametre(bytePerPixelStr);
	int bytePerPixel = stringToInt(param);
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
	cadre=Cadre::getInstance(); // new Cadre(posXCadre,posYCadre,configuration,surfaces,this);
	background = new Background(posXbackground,posYbackground, configuration, surfaces, this);


#ifndef NOUNIT
	int moiX = (windowWidth)/2;
	int moiY = (windowHeight)/2;
	string typeArme="armeDefaut";
	string typeBalle="BalleDefaut";

	unitees.push_back(new UniteJoueurJouable(moiX,moiY, typeArme, typeBalle));
	int newX = 100;
	int newY=newX;
	unitees.push_back(new UniteNonJoueur(newX, newY, typeArme, typeBalle));
#endif


	return 0;
}



/**
* \brief
*/
int Application::update ()
{
//	musique->playMusique(AMBIANT);

	int gameover = 0;
	/* message pump */
	while (!gameover)
	{
	    timers->raffraichissement();

		/* look for an event */
		if (SDL_PollEvent(&event)) {

			switch (event.type) {
				case SDL_KEYDOWN:
					switch( event.key.keysym.sym ) {
						case SDLK_UP:
							debug->print("Touche haut appuyee");
							keyValue.isArrowUpPressed=true;
							background->setSpeedKeyUpPressed();
							break;
						case SDLK_DOWN:
							debug->print("Touche bas appuyee");
							keyValue.isArrowDownPressed=true;
							background->setSpeedKeyDownPressed();
							break;
						case SDLK_LEFT:
							debug->print("Touche gauche appuyee");
							keyValue.isArrowLeftPressed=true;
							background->setSpeedKeyLeftPressed();
							break;
						case SDLK_RIGHT:
							debug->print("Touche droite appuyee");
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
							debug->print("Touche haut relache");
							keyValue.isArrowUpPressed=false;
							background->setSpeedKeyUpReleased();
							break;
						case SDLK_DOWN:
							debug->print("Touche bas relache");
							keyValue.isArrowDownPressed=false;
							background->setSpeedKeyDownReleased();
							break;
						case SDLK_LEFT:
							debug->print("Touche gauche relache");
							keyValue.isArrowLeftPressed=false;
							background->setSpeedKeyLeftReleased();
							break;
						case SDLK_RIGHT:
							debug->print("Touche droite relache");
							keyValue.isArrowRightPressed=false;
							background->setSpeedKeyRightReleased();
							break;
						default: break;
					}
					break;
				//on veut récupérer les positions de la souris lors d'un clic et déterminer s'il s'agit d'une action sur le menu ou sur le terrain (Tir)
				//Le clic ne sera effectif que lorsque l'on aura relaché le bouton.
				case SDL_MOUSEBUTTONDOWN:
				{
					int x = event.motion.x;
					int y = event.motion.y;
					if(cadre->actionSouris(x,y)){
						debug->print("Clic sur le cadre");
						keyValue.isLeftMouseClickOnCadre=true;
						keyValue.isLeftMouseClickOnBackground=false;
					}
					else {
						debug->print("Clic sur le terrain");
						keyValue.isLeftMouseClickOnCadre=false;
						keyValue.isLeftMouseClickOnBackground=true;
					}
				}
					break;
				case SDL_MOUSEBUTTONUP:

					if(keyValue.isLeftMouseClickOnCadre)
						cadre->handleInput(event);

					debug->print("Bouton souris relache");
					keyValue.isLeftMouseClickOnCadre=false;
					keyValue.isLeftMouseClickOnBackground=false;

					break;
				default: break;
			}// end switch

			for (list<Unite*>::iterator itUnite = unitees.begin(); itUnite != unitees.end(); itUnite++) {
				// controle spécifique au joueur, soit une unité->traitement par l'objet
				if((*itUnite)->typeUnite==PJOUEUR_JOUABLE) {
					(*itUnite)->handleInput(event);
					break;
				}
			}

		}// end SDL_PollEvent

		//----------------------
		// UPDATING ROUTINE
		//----------------------
        if(timers->lanceToutesLesMs(16,TIMER_UPDATE)) {
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
        }

        if(timers->lanceToutesLesMs(16,TIMER_AFFICHE))
            draw();
	} // end while


	return 0;
}


/**
* \brief
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

