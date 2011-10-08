
#include "Balle.h"


int Balle::load()
{
	Configuration* configuration=Configuration::getInstance();
	Surfaces* surfaces=Surfaces::getInstance();

	animation = surfaces->getAnimation(type.c_str());
	imageCourante=(*animation).begin();
	boitesCollisions = surfaces->getBoitesCollisions(type.c_str());
	this->degats = stringToInt(configuration->getValeurParametre((type+string(".degat")).c_str()));
	this->vitesse = stringToFloat(configuration->getValeurParametre((type+string(".vitesse")).c_str()));
	this->vie = stringToInt(configuration->getValeurParametre((type+string(".vie")).c_str()));

	return 0;
}

int Balle::update() 
{
	// Se d�place et g�re les collisions.
	float decalX = velX + application->background->velXbackground;
	float decalY = velY + application->background->velYbackground; 

	if((velX!=0)&&(velY!=0)){
		if (detecteCollisions(decalX, decalY)){
			velX=0;
			velY=0;
		}
	}	

	posX += decalX; 
	posY += decalY;

	return 0;
}


/*
*\brief d�tection des collisions avec d'autre objets.
*\param decalX d�calage horizontal en pixels.
*\param decalY d�calage vertical en pixels.
*\return true si une collision a �t� d�tect�, false dans l'autre cas.
*/
bool Balle::detecteCollisions(float& decalX, float& decalY)
{
	float newX = posX + decalX;
	float newY = posY + decalY;

	// d�tection background unitees;
	list<Unite*>::iterator itUnite = application->unitees.begin();
	while (itUnite != application->unitees.end()) {
		if (( (*itUnite)->identifiantJoueur!=identifiantJoueur)&&(collision(newX, newY, *boitesCollisions, (*itUnite)->posX, (*itUnite)->posY, *(*itUnite)->boitesCollisions))) {
			(*itUnite)->vie-=degats;
			vie=0;
			cout << "collision unite" << endl;		
			return true;
		}
		itUnite++;
	}
	float posPixelXBackground=application->background->posXbackground;
	float posPixelYBackground=application->background->posYbackground;

	if(collision(newX,newY,*boitesCollisions, posPixelXBackground, posPixelYBackground,*(application->background->boitesCollisions))){
		this->vie=0;
		//cout << "collision background" <<endl;
		return true;
	}

	return false;
}



int Balle::draw(SDL_Surface *screen)
{
	if (angle == 0)
		afficheEcran((int)posX, (int)posY, screen, *imageCourante);
	else {
		SDL_Surface* surfaceAfficher = pivoteSurface(*imageCourante,angle,true);
		surfaceAfficher = conversionFormatAffichable(surfaceAfficher, false);
		
		Uint32 colorkey = SDL_MapRGB( surfaceAfficher->format, 0, 0xFF, 0xFF ); 
		SDL_SetColorKey( surfaceAfficher, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey ); 

		int posX2 = (2*(int)posX + (*imageCourante)->w - surfaceAfficher->w)/2;
		int posY2 = (2*(int)posY + (*imageCourante)->h - surfaceAfficher->h)/2;

		afficheEcran((int)posX2, (int)posY2, screen, surfaceAfficher);
		SDL_FreeSurface(surfaceAfficher);
	}
	return 0;	
}


int Balle::handleInput(SDL_Event &event)
{
	return 0;
}

Balle* Balle::clone()
{
	return new Balle(*this);
}

//--------------------------------------------------------
UsineBalles* UsineBalles::_singleton=0;


UsineBalles* UsineBalles::getInstance()
{
	if(_singleton==0) {
		_singleton=new UsineBalles();
		if(_singleton->chargement()==false) {
			MessageBox(NULL, "L'usine de balles n'a pas pu etre charge!", "FATAL ERROR", MB_OK|MB_ICONERROR);
			_singleton=destruction();
		}
	}
	return _singleton;
}

UsineBalles* UsineBalles::destruction()
{
	delete _singleton;
	_singleton=0;
	return _singleton;
}

UsineBalles::UsineBalles()
{
}

bool UsineBalles::chargement()
{
	ifstream fichier(fichierConfigBalle.c_str());
	if(fichier.fail()) {
		cout << "Impossible d'ouvrir le fichier " << fichierConfigBalle << endl;
		return false;
	}

	string ligne;
	while(getline(fichier,ligne)) {
	
		stringstream ss(ligne);
		string nouvelleClef,nouvelleValeur,nouveauNom;
		getline(ss,nouvelleClef,';');
		getline(ss,nouvelleValeur,';');

		string::size_type posPoint=nouvelleClef.find_first_of('.');
		if(posPoint!=string::npos) {
			nouveauNom=nouvelleClef.substr(0,posPoint);
		
			map<string, Balle*>::iterator it = modelesBalles.find(nouveauNom);
			if(it==modelesBalles.end()) {
				int posX,posY,identifiantJoueur=0;
				double angle=0;
				Balle* balle = new Balle(posX,posY,angle,nouveauNom,identifiantJoueur);
				modelesBalles.insert(pair<string,Balle*>(nouveauNom,balle));
			}
		}
	}


	fichier.close();
	return true;
}

