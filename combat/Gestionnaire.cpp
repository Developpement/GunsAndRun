#include "Gestionnaire.h"
#include "Form_quitter.h"
#include <windows.h>

Gestionnaire* Gestionnaire::_singleton=0;

/**
* \brief
*/
Gestionnaire* Gestionnaire::getInstance()
{
	if(_singleton==0) {
		_singleton=new Gestionnaire();
	}
	return _singleton;
}


/**
* \brief
*/
Gestionnaire* Gestionnaire::destruction()
{
	delete _singleton;
	_singleton=0;
	return _singleton;
}


/**
* \brief
*/
Gestionnaire::Gestionnaire()
{
	configuration=ConfigurationJeu::getInstance();
	timers=Horloge::getInstance();
//	musique=Musique::getInstance();
	clavier=Clavier::getInstance();
	souris=Souris::getInstance();

	debug=Debug::getInstance();

	gameover=false;
	idCpt=0;
	debug->print("Gestionnaire constructeur");
}

/**
* \brief
*/
Gestionnaire::~Gestionnaire()
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
	cadre=Cadre::destruction();
	background=Background::destruction();

	/* free the background surface */
	SDL_FreeSurface(screen);
	/* cleanup SDL */
	SDL_Quit();
}

/**
* \brief
*/
int Gestionnaire::init ()
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
	/*int posXbackground = stringToInt(configuration->getValeurParametre("joueurJouable.posX"));
	int posYbackground = stringToInt(configuration->getValeurParametre("joueurJouable.posY"));*/
	cadre=Cadre::getInstance();
	
	background=Background::getInstance();
	//background = new Background(posXbackground,posYbackground, string("map"));

#ifndef NOUNIT
	int moiX = (windowWidth)/2;
	int moiY = (windowHeight)/2;
	string typeArme="armeDefaut";
	string typeBalle="BalleDefaut";

	unitees.push_back(new UniteJoueurJouable(moiX,moiY, typeArme, typeBalle));
	//int newX = 100;
	//int newY = newX;
	//unitees.push_back(new UniteNonJoueur(newX, newY, typeArme, typeBalle));
#endif

#ifndef NOBUILDING
	string baseNomBatiment="Batiment_";
	int cptBatiment=0;
	while (1) {
		string cleBatiment=baseNomBatiment+toString(cptBatiment);
		string cleTypeBatiment=cleBatiment+".type";
		string typeBatiment = configuration->getValeurParametre(cleTypeBatiment.c_str(),false);
		if(typeBatiment.empty()==false) {
			if(typeBatiment.compare("Marche")==0) {
				string posXBatiment = configuration->getValeurParametre((cleBatiment+string(".posX")).c_str());
				string posYBatiment = configuration->getValeurParametre((cleBatiment+string(".posY")).c_str());
				batiments.push_back(new Marche(stringToInt(posXBatiment), stringToInt(posYBatiment) ) );		
			}
		}
		else break;
		cptBatiment++;
	}
	
#endif
	return 0;
}



/**
* \brief
*/
int Gestionnaire::update ()
{
//	musique->playMusique(AMBIANT);

	/* message pump */
	while (gameover==false)
	{
	    timers->raffraichissement();

		/* look for an event */
		if (SDL_PollEvent(&event)) {
			clavier->handleInput(event);
			souris->handleInput(event);
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
			
			list<Batiment*>::iterator itBatiment;
            for (itBatiment = batiments.begin(); itBatiment != batiments.end(); itBatiment++) {
                (*itBatiment)->update();
            }



            // destruction des objets qui doivent l'être
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
int Gestionnaire::draw()
{
	background->draw(screen);

	list<Balle*>::iterator itBalle;
	for (itBalle = balles.begin(); itBalle != balles.end(); itBalle++) {
		(*itBalle)->draw(screen);
	}

	list<Batiment*>::iterator itBatiment;
    for (itBatiment = batiments.begin(); itBatiment != batiments.end(); itBatiment++) {
		(*itBatiment)->draw(screen);
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

void Gestionnaire::close()
{
	combat::Form_quitter formQuitter;
	if(formQuitter.Form_quitter_clicked==TRUE)
		gameover = true;
}
