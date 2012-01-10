
#include "Arme.h"


/**
* \brief
*/
Arme::Arme(float& posX, float& posY, double& angle, string& typeArme,string& typeBalle, int typeUnite, int identifiantJoueur)
{
	timers = Horloge::getInstance();
	this->type=typeArme;
	this->sousTypeBalle=typeBalle;

	this->typeUnite= typeUnite;
	application=Gestionnaire::getInstance();
	surfaces=Surfaces::getInstance();
	usineBalles=UsineBalles::getInstance();
	configuration=ConfigurationJeu::getInstance();

	load();

	this->identifiantJoueur = identifiantJoueur;
	this->posX = static_cast<float>(posX);
	this->posY = static_cast<float>(posY);
	velX = 1;
	velY = 1;
	tir=false;
	
	// Nombre de balles par seconde
	
	string cadenceKey = typeArme+".cadence";
	
	cadence = stringToInt(configuration->getValeurParametre(cadenceKey.c_str()));
	
	this->angle=angle;
}

/**
* \brief
*/
int Arme::load()
{
	animation = surfaces->getAnimation((char*)type.c_str());
	imageCourante=(*animation).begin();
	boitesCollisions = surfaces->getBoitesCollisions((char*)type.c_str());

	return 0;
}

/**
* \brief
*/
int Arme::handleInput(SDL_Event& event)
{
	return 0;
}

/**
* \brief
*/
int Arme::update()
{
	if (tir == true) {
		if(timers->timerInferieurHorloge(timerCadence)) {
			timers->horlogePlusDelai(timerCadence,cadence);
			if (application->balles.size()>=MAX_BALLES)
				application->balles.erase(application->balles.begin());

			application->balles.push_back(usineBalles->creationBalle(posX, posY, angle, sousTypeBalle, identifiantJoueur));
		}
	}
	if(typeUnite==PNON_JOUEUR){
		velX=application->background->velXbackground;
		velY=application->background->velYbackground;
		posX+=velX;
		posY+=velY;
	}

	return 0;
}

/**
* \brief
*/
void Arme::debutTir()
{
	tir = true;
}

/**
* \brief
*/
void Arme::arretTir()
{
	tir = false;
}

/**
* \brief
*/
void Arme::updateAngle(double &angle)
{
	this->angle = angle;
}

/**
* \brief
*/
int Arme::draw(SDL_Surface* screen)
{
	if (angle == 0)
		afficheEcran(posX, posY, screen, *imageCourante);
	else {
		SDL_Surface* surfaceAfficher = pivoteSurface(*imageCourante,angle,true);
		surfaceAfficher = conversionFormatAffichable(surfaceAfficher, false);

		Uint32 colorkey = SDL_MapRGB( surfaceAfficher->format, 0, 0xFF, 0xFF );
		SDL_SetColorKey( surfaceAfficher, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey );

		float posX2 = (2*posX + (*imageCourante)->w - surfaceAfficher->w)/2;
		float posY2 = (2*posY + (*imageCourante)->h - surfaceAfficher->h)/2;

		afficheEcran(posX2, posY2, screen, surfaceAfficher);
		SDL_FreeSurface(surfaceAfficher);
	}
	return 0;
}



//--------------------------------------------------------
UsineArmes* UsineArmes::_singleton=0;

/**
* \brief
*/
UsineArmes* UsineArmes::getInstance()
{
	if(_singleton==0) {
		_singleton=new UsineArmes();
		if(_singleton->chargement()==false) {
			MessageBox(NULL, "L'usine d'armes n'a pas pu etre charge!", "FATAL ERROR", MB_OK|MB_ICONERROR);
			_singleton=destruction();
		}
	}
	return _singleton;
}

/**
* \brief
*/
UsineArmes* UsineArmes::destruction()
{
	delete _singleton;
	_singleton=0;
	return _singleton;
}

/**
* \brief
*/
UsineArmes::UsineArmes()
{
	debug=Debug::getInstance();
}

/**
* \brief
*/
UsineArmes::~UsineArmes()
{
	for(map<string,Arme*>::iterator it=modelesArmes.begin();it!=modelesArmes.end();it++)
		delete it->second;
	modelesArmes.clear();

	debug->print("UsineArmes destructeur appele.");
}

/**
* \brief
*/
bool UsineArmes::chargement()
{
	ifstream fichier(fichierConfigArme.c_str());
	if(fichier.fail()) {
		debug->print("Impossible d'ouvrir le fichier "+fichierConfigArme);
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

			map<string, Arme*>::iterator it = modelesArmes.find(nouveauNom);
			if(it==modelesArmes.end()) {
                float posX=0;
				float posY=0;
				//int identifiantJoueur=0;
				double angle=0;
				string balleDefaut = "BalleDefaut";
				Arme* arme = new Arme(posX,posY, angle, nouveauNom, balleDefaut, NON_DEFINI,0);
				modelesArmes.insert(pair<string,Arme*>(nouveauNom,arme));
			}
		}
	}


	fichier.close();
	return true;
}

/**
* \brief
*/
Arme* Arme::clone()
{
	return new Arme(*this);
}
