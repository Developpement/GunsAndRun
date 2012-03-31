#include "Texte.h"


Fonts* Fonts::_singleton = 0;



SDL_Surface* Texte::getSurface()
{
	return surface;
}


Texte::Texte(string& typeFont, int& taille, string& message, SDL_Color& couleur, int largeur, int hauteur)
{
	font = Fonts::getInstance()->getTTF_Font(typeFont,taille);
	surface = TTF_RenderText_Solid( font, message.c_str(), couleur);
	if(surface) {
		if((largeur!=0)&&(hauteur!=0))
			surface=redimensionneSurface(surface,largeur,hauteur,false);
#if 0
		insertDelimiteurSurface(surface,5);
#endif
	}
	else Debug::getInstance()->print("Impossible d'obtenir une surface à partir du font "+typeFont);
}

Texte::~Texte()
{
	SDL_FreeSurface(surface);
}

  
TTF_Font* Fonts::getTTF_Font(string& type, int& taille)
{
	for (vector<Font*>::iterator it=fontList.begin(); it!=fontList.end();it++)	{
		if(((*it)->type.compare(type)==0)&&((*it)->taille==taille))
			return (*it)->font;
	}
	fontList.push_back(new Font(type,taille));
	return fontList.back()->font;
}

Fonts::Fonts()
{
}

Fonts::~Fonts()
{
	for (vector<Font*>::iterator it=fontList.begin(); it!=fontList.end();it++) {
		delete *it;
		*it = 0;
	}
}



Fonts* Fonts::getInstance()
{
	if(_singleton==0) {
		_singleton=new Fonts();
	}
	return _singleton;
}

Fonts* Fonts::destruction()
{
	if(_singleton) {
		delete _singleton;
		_singleton=0;
	}
	return _singleton;
}


Font::Font(string& type, int& taille)
{
	font = TTF_OpenFont( type.c_str(), taille );
	if(font==0)
		Debug::getInstance()->print("Impossible de charger le font " + type);
	this->type = type;
	this->taille=taille;
}

Font::~Font()
{
	TTF_CloseFont( font );
	font=0;
}




