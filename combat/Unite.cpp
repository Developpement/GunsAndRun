#include "Unite.h"



Unite::Unite()
{
	debug=Debug::getInstance();
	debug->print("Constructeur Unite appele");
}

// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------UniteJoueurJouable------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
UniteJoueurJouable::UniteJoueurJouable(int& posX, int& posY, string& typeArme, string& typeBalle)
{
#ifndef NOUNIT
	application=Gestionnaire::getInstance();
	configuration=ConfigurationJeu::getInstance();
	surfaces=Surfaces::getInstance();
	usineArmes=UsineArmes::getInstance();
	// On incr�mente l'identifiant pour que toutes les unit�es aient un identifiant diff�rent.
	this->identifiantJoueur=Gestionnaire::getInstance()->idCpt++;

	this->typeArme=typeArme;
	this->typeBalle=typeBalle;

	animation=0;
	boitesCollisions=0;
	angle = 0;
	etat = IMMOBILE;
	typeUnite = PJOUEUR_JOUABLE;

	load();

	this->posX = static_cast<float>(posX - (*animation)[0]->w/2);
	this->posY = static_cast<float>(posY - (*animation)[0]->h/2);
	velX = 0;
	velY = 0;

	// ARME de l'unit�.
	arme = usineArmes->creationArme(static_cast<int>(this->posX), static_cast<int>(this->posY), angle, typeArme, typeUnite, identifiantJoueur);
	Cadre::getInstance()->changeImageBouttonArme(typeArme);
#endif
}


int UniteJoueurJouable::load()
{
#ifndef NOUNIT
	// graphics
	animation = surfaces->getAnimation("uniteJoueur");
	imageUniteCourante=(*animation).begin();
	boitesCollisions = surfaces->getBoitesCollisions("uniteJoueur");

	//autres
	vie = stringToInt(configuration->getValeurParametre("joueurJouable.StartLife"));
#endif
	return 0;
}



int UniteJoueurJouable::handleInput(SDL_Event& event)
{
#ifndef NOUNIT
	switch (event.type) {

		case SDL_MOUSEMOTION:
			// on r�cup�re les positions de la souris:
			//if (typeUnite == PJ_JOUABLE)
			{
				int x = event.motion.x;
				int y = event.motion.y;
				// calcul de l'angle pour l'unite du joueur:
				int centreX = static_cast<int>((posX*2 + (*imageUniteCourante)->w)/2);
				int centreY = static_cast<int>((posY*2 + (*imageUniteCourante)->h)/2);
				angle = calculAngle(centreX, centreY, x, y);
				arme->updateAngle(angle);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			//if ((typeUnite == PJ_JOUABLE)&&(application->keyValue.isLeftMouseClickOnBackground)) {
				//debug->print("Feu!!!" << endl;
				arme->debutTir();
			//}
			break;
		case SDL_MOUSEBUTTONUP:
			//if (typeUnite == PJ_JOUABLE) {
				debug->print("Stop Tir (nb balles="+toStringA(application->balles.size())+").");
				arme->arretTir();
			//}
			break;
	}// end switch

	arme->handleInput(event);
#endif
	return 0;
}


int UniteJoueurJouable::update()
{
#ifndef NOUNIT
	if(typeUnite==PNON_JOUEUR){
		velX=application->background->velXbackground;
		velY=application->background->velYbackground;
	}

	posX += velX;
	posY += velY;

	arme->update();
#endif
	return 0;
}

int UniteJoueurJouable::draw(SDL_Surface* screen)
{
#ifndef NOUNIT
	if (angle == 0)
		dessineSurface(static_cast<int>(posX), static_cast<int>(posY), screen, *imageUniteCourante);
	else {
		SDL_Surface* surfaceAfficher = pivoteSurface(*imageUniteCourante,angle,true);
		surfaceAfficher = conversionFormatAffichable(surfaceAfficher, false);

		Uint32 colorkey = SDL_MapRGB( surfaceAfficher->format, 0, 0xFF, 0xFF );
		SDL_SetColorKey( surfaceAfficher, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey );

		int posX2 = static_cast<int>((2*posX + (*imageUniteCourante)->w - surfaceAfficher->w)/2);
		int posY2 = static_cast<int>((2*posY + (*imageUniteCourante)->h - surfaceAfficher->h)/2);

		dessineSurface(posX2, posY2, screen, surfaceAfficher);
		SDL_FreeSurface(surfaceAfficher);
	}

	arme->draw(screen);
#endif
	return 0;
}



// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
UniteNonJoueur::UniteNonJoueur(int& posX, int& posY, string& typeArme, string& typeBalle)
{
#ifndef NOUNIT
	application=Gestionnaire::getInstance();
	configuration=ConfigurationJeu::getInstance();
	surfaces=Surfaces::getInstance();
	usineArmes=UsineArmes::getInstance();
	// On incr�mente l'identifiant pour que toutes les unit�es aient un identifiant diff�rent.
	this->identifiantJoueur=Gestionnaire::getInstance()->idCpt++;

	this->typeArme=typeArme;
	this->typeBalle=typeBalle;

	animation=0;
	boitesCollisions=0;
	angle = 0;
	etat = IMMOBILE;
	typeUnite = PNON_JOUEUR;

	load();

	this->posX = static_cast<float>(posX - (*animation)[0]->w/2) - stringToInt(configuration->getValeurParametre("joueurJouable.posX"));
	this->posY = static_cast<float>(posY - (*animation)[0]->h/2) - stringToInt(configuration->getValeurParametre("joueurJouable.posY"));
	velX = 0;
	velY = 0;

	// ARME de l'unit�.
	arme = usineArmes->creationArme(static_cast<int>(this->posX), static_cast<int>(this->posY), angle, typeArme, typeUnite, identifiantJoueur);
#endif
}


int UniteNonJoueur::load()
{
#ifndef NOUNIT
	// graphics
	animation = surfaces->getAnimation("uniteJoueur");
	imageUniteCourante=(*animation).begin();
	boitesCollisions = surfaces->getBoitesCollisions("uniteJoueur");

	//autres
	vie=stringToInt(configuration->getValeurParametre("nonJoueur.StartLife"));
#endif
	return 0;
}



int UniteNonJoueur::handleInput(SDL_Event& event)
{
	return 0;
}


int UniteNonJoueur::update()
{
#ifndef NOUNIT
	velX=application->background->velXbackground;
	velY=application->background->velYbackground;

	posX += velX;
	posY += velY;

	arme->update();
#endif
	return 0;
}

int UniteNonJoueur::draw(SDL_Surface* screen)
{
#ifndef NOUNIT
	if (angle == 0)
		dessineSurface(static_cast<int>(posX), static_cast<int>(posY), screen, *imageUniteCourante);
	else {
		SDL_Surface* surfaceAfficher = pivoteSurface(*imageUniteCourante,angle,true);
		surfaceAfficher = conversionFormatAffichable(surfaceAfficher, false);

		Uint32 colorkey = SDL_MapRGB( surfaceAfficher->format, 0, 0xFF, 0xFF );
		SDL_SetColorKey( surfaceAfficher, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey );

		int posX2 = static_cast<int>((2*posX + (*imageUniteCourante)->w - surfaceAfficher->w)/2);
		int posY2 = static_cast<int>((2*posY + (*imageUniteCourante)->h - surfaceAfficher->h)/2);

		dessineSurface(posX2, posY2, screen, surfaceAfficher);
		SDL_FreeSurface(surfaceAfficher);
	}

	arme->draw(screen);
#endif
	return 0;
}
