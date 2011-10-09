#include "DisplayFormatSurfaces.h"


Surfaces* Surfaces::_singleton = 0;

/**
* \brief Force l'existance unique d'un objet Surfaces.
* \details La premi�re fois que la m�thode est appel�e, une instance de la classe est cr�e. Les fois suivantes, seul le pointeur vers la premi�re instance est appel�e
* 			et aucune autre instance n'est cr��e.
* \return Le pointeur vers l'unique instance de type Surfaces.
*/
Surfaces* Surfaces::getInstance()
{
	if(_singleton==0) {
		_singleton=new Surfaces();
		if(_singleton->load()==false) {
			delete _singleton;
			_singleton=0;
		}
	}
	return _singleton;
}

/**
* \brief Lib�re la m�moire allou�e � l'unique instance de la classe Surfaces.
* \return Pointeur vers l'adresse 0.
*/
Surfaces* Surfaces::destruction()
{
	delete _singleton;
	_singleton=0;
	return _singleton;
}

Surfaces::Surfaces()
{
	configuration=Configuration::getInstance();
	cout << "Constructeur Surfaces apelle" << endl;
}

/*
* \brief	R�cup�re une animation pr�alablement charg�e.
*/
vector<SDL_Surface*>* Surfaces::getAnimation (const char* nomAnimation)
{
	map< string, vector<SDL_Surface*> >::iterator it = animList.find(string(nomAnimation));
	if(it==animList.end()) {
		string err=string("Impossible de trouver l'animation nomm�e {")+string(nomAnimation)+string("}.");
		MessageBoxA(NULL,err.c_str(),"Erreur!",MB_OK|MB_ICONERROR);
		//TODO: Affichage de l'erreur (message clair)
		//configuration->getValeurParametre(nomAnimation);
		//load();
		//it = animList.find(string(name));
	}
	return &(it->second);
}
/*
* \brief	R�cup�re une animation pr�alablement charg�e et la redimensionne en �crasant l'origine.
*/
vector<SDL_Surface*>* Surfaces::getAnimation (const char* name, int& largeur, int& hauteur)
{
	map< string, vector<SDL_Surface*> >::iterator it = animList.find(string(name));
	if(it==animList.end()) {
		configuration->getValeurParametre(name);
		load();
		it = animList.find(string(name));
	}

	for(vector<SDL_Surface*>::iterator itSurfaceRedimentionnee=it->second.begin();itSurfaceRedimentionnee!=it->second.end();itSurfaceRedimentionnee++){
		if(((*itSurfaceRedimentionnee)->w!=largeur)||((*itSurfaceRedimentionnee)->h!=hauteur))
			*itSurfaceRedimentionnee=redimensionneSurface(*itSurfaceRedimentionnee,	largeur, hauteur, false);
	}
	return &(it->second);
}

pair<int,int> Surfaces::getSizeAnimationFirstImage (const char* name)
{
	map< string, vector<SDL_Surface*> >::iterator it = animList.find(string(name));
	pair<int,int> taille(it->second[0]->w,it->second[0]->h);
	return taille;
}

/*
* \brief	R�cup�re un vecteur de boites de collision � dimension fix�es au pr�alable.
*/
vector<SDL_Rect>* Surfaces::getBoitesCollisions (const char* name)
{
	map< string, vector<SDL_Rect> >::iterator it = collisionList.find(string(name));
	if (it != collisionList.end()) {
		return & collisionList[string(name)];
	}
	else {
		return 0;
	}
}

/*
* \brief	R�cup�re un vecteur de boites de collisions en modifiant au pr�alable la taille des images.
*/
vector<SDL_Rect>* Surfaces::getBoitesCollisions (const char* name, int& largeur, int& hauteur)
{
	map< string, vector<SDL_Rect> >::iterator it = collisionList.find(string(name));
	if (it != collisionList.end()) {
		if((it->second.begin()->w!=largeur)||(it->second.begin()->h!=hauteur)){
			for(vector<SDL_Rect>::iterator itRect=it->second.begin();itRect!=it->second.end();itRect++){
				//     1280/800=1.6  -> largeur=800, (old)1280/1.6=800
				// On est pas au pixel pr�s, donc on peut se permettre ce genre de calcul
				pair<int,int> taille = getSizeAnimationFirstImage(name);
				itRect->w /=(Uint16)ceil((float)taille.first/(float)largeur);
				itRect->h /=(Uint16)ceil((float)taille.second/(float)hauteur);
			}//end for
		}// end else
		return & collisionList[string(name)];
	}//end if
	else return 0;
}

int Surfaces::addAnimation (string nomAnim, string imageNeutre)
{
	//string imageNeutre = configuration->getValeurParametre(nomAnim,fichierListeImages);
	string::size_type pos = imageNeutre.find_first_of(".");
	string format;

	if(pos != string::npos) {
		format = imageNeutre.substr(pos);
		imageNeutre.erase(pos);
	}
	else {
		format = "bmp";
	}

	string buf = imageNeutre + format;

	vector<SDL_Surface*> animationCourante;
	SDL_Surface* surfaceBrute;
	SDL_Surface* surfaceOptimisee;
	unsigned int i = 1;

	do {
		surfaceBrute = IMG_Load(buf.c_str());
		surfaceOptimisee = 0;
		if (surfaceBrute != 0) {
			surfaceOptimisee = SDL_DisplayFormat(surfaceBrute);
			SDL_FreeSurface(surfaceBrute);
			if (surfaceOptimisee != 0) {
				Uint32 colorkey = SDL_MapRGB( surfaceOptimisee->format, 0, 0xFF, 0xFF );
				SDL_SetColorKey( surfaceOptimisee, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey );
			}
		}


		if ( surfaceOptimisee == 0 ) {
			cout << "IMG_Load error " << IMG_GetError () << endl << ", with " << buf << endl;
			break;
		}
		else {
			animationCourante.push_back(surfaceOptimisee);
		}

		buf = imageNeutre + "_" + toString(i) + format;
		i++;
	}while(surfaceOptimisee!=0);

	animList.insert(pair< string, vector<SDL_Surface*> >(string(nomAnim),animationCourante));

	return 0;
}

int Surfaces::addCollisionBox(string nomAnim, string imageNeutre)
{
	//string imageNeutre = configuration->getValeurParametre(nomAnim,fichierListeImages);
	string::size_type pos = imageNeutre.find_first_of(".");
	string format;

	if(pos != string::npos) {
		format = imageNeutre.substr(pos);
		imageNeutre.erase(pos);
		imageNeutre += collisionFichierSuffix;
	}
	else {
		format = "bmp";
	}

	string buf = imageNeutre + format;

	vector<SDL_Rect> collisions;
	SDL_Surface* surfaceBrute;
	unsigned int i = 1;

	do {
		surfaceBrute = IMG_Load(buf.c_str());
		if (surfaceBrute != 0) {
			collisions = obtienRectCollisionSurface(surfaceBrute);
			SDL_FreeSurface(surfaceBrute);
		}
		else {
			cout << "IMG_Load error " << IMG_GetError () << endl << ", with " << buf << endl;
			break;
		}

		buf = imageNeutre + "_" + toString(i) + format;
		i++;
	}while(1);

	collisionList.insert(pair< string, vector<SDL_Rect> >(string(nomAnim),collisions));

	return 0;
}

/**
* \brief charge toutes les animations et les boitiers de collision � partir de cette m�thode.
* \details Cette m�thode ne charge les images que si le conteneur est vide.
* \return true en cas de succ�s, false en cas d'�chec.
*/
bool Surfaces::load()
{
	if((!animList.empty())||(!collisionList.empty())) {
		cout << "Erreur: Tentative de chargement d'images d�j� en m�moire." << endl;
		return false;
	}

	cout << "Chargement des animations et des boites de collisions." << endl;

	// Ouverture du fichier d'images en lecture
	ifstream fichier (fichierConfigImages.c_str());
	if (fichier.fail()) {
		cout << "Cannot write in file " << fichierConfigImages << endl;
		return false;
	}

	string line, key, value;
	while(getline(fichier, line)) {
		stringstream ss;
		ss << line;
		getline(ss, key, ';');
		getline(ss, value, ';');

		addAnimation(key, value);
		addCollisionBox(key, value);
	}
	fichier.close();

	return true;
}
