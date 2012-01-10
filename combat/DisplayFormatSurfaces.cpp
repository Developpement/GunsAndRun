#include "DisplayFormatSurfaces.h"


Surfaces* Surfaces::_singleton = 0;

/**
* \brief Force l'existance unique d'un objet Surfaces.
* \details La première fois que la méthode est appelée, une instance de la classe est crée. Les fois suivantes, seul le pointeur vers la première instance est appelée
* 			et aucune autre instance n'est créée.
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
* \brief Libère la mémoire allouée à l'unique instance de la classe Surfaces.
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
	debug=Debug::getInstance();
	configuration=ConfigurationJeu::getInstance();
	debug->print("Constructeur Surfaces apelle");
}

/*
* \brief	Récupère une animation préalablement chargée.
*/
vector<SDL_Surface*>* Surfaces::getAnimation (const char* nomAnimation)
{
	map< string, vector<SDL_Surface*> >::iterator it = animList.find(string(nomAnimation));
	if(it==animList.end()) {
		string err=string("Impossible de trouver l'animation nommée {")+string(nomAnimation)+string("}.");
		MessageBoxA(NULL,err.c_str(),"Erreur!",MB_OK|MB_ICONERROR);
		//TODO: Affichage de l'erreur (message clair)
		//configuration->getValeurParametre(nomAnimation);
		//load();
		//it = animList.find(string(name));
	}
	return &(it->second);
}
/*
* \brief	Récupère une animation préalablement chargée et la redimensionne en écrasant l'origine.
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
* \brief	Récupère un vecteur de boites de collision à dimension fixées au préalable.
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
* \brief	Récupère un vecteur de boites de collisions en modifiant au préalable la taille des images.
*/
vector<SDL_Rect>* Surfaces::getBoitesCollisions (const char* name, int& largeur, int& hauteur)
{
	map< string, vector<SDL_Rect> >::iterator it = collisionList.find(string(name));
	if (it != collisionList.end()) {
		if((it->second.begin()->w!=largeur)||(it->second.begin()->h!=hauteur)){
			for(vector<SDL_Rect>::iterator itRect=it->second.begin();itRect!=it->second.end();itRect++){
				//     1280/800=1.6  -> largeur=800, (old)1280/1.6=800
				// On est pas au pixel près, donc on peut se permettre ce genre de calcul
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
			debug->print("IMG_Load error "+toStringA(IMG_GetError())+"\n, with "+buf);
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
			debug->print("IMG_Load error "+toStringA(IMG_GetError())+"\n, with "+buf);
			break;
		}

		buf = imageNeutre + "_" + toString(i) + format;
		i++;
	}while(1);

	collisionList.insert(pair< string, vector<SDL_Rect> >(string(nomAnim),collisions));

	return 0;
}

/**
* \brief charge toutes les animations et les boitiers de collision à partir de cette méthode.
* \details Cette méthode ne charge les images que si le conteneur est vide.
* \return true en cas de succès, false en cas d'échec.
*/
bool Surfaces::load()
{
	if((!animList.empty())||(!collisionList.empty())) {
		debug->print("Erreur: Tentative de chargement d'images déjà en mémoire.");
		return false;
	}

	debug->print("Chargement des animations et des boites de collisions.");

	// Ouverture du fichier d'images en lecture
	ifstream fichier (fichierConfigImages.c_str());
	if (fichier.fail()) {
		debug->print("Cannot write in file "+fichierConfigImages);
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
