#include "Texte.h"


Fonts* Fonts::_singleton = 0;



SDL_Surface* Texte::getSurface()
{
	return message;
}


Texte::Texte(string& typeFont, int& taille, string& msg, SDL_Color& couleur)
{
	font = Fonts::getInstance()->getTTF_Font(typeFont,taille);
	this->message = TTF_RenderText_Solid( font, msg.c_str(), couleur );
	if(message==0)
		cout << "erreur" << endl;
}

Texte::~Texte()
{
	SDL_FreeSurface( message );
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
		cout << "erreur" << endl;
	this->type = type;
	this->taille=taille;
}

Font::~Font()
{
	TTF_CloseFont( font );
	font=0;
}




