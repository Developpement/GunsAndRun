#pragma once

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "Debug.h"
#include "Outils.h"
#include "Affichage.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

static string CASLONBOLD="CaslonBold.ttf"	;

static SDL_Color couleur_noir = {0,0,0};



class Font
{
public:
  string type;
  int taille;
  TTF_Font* font;

  Font(string& type, int& taille);
  ~Font();
};


class Fonts
{
	static Fonts* _singleton;
	
	vector<Font*> fontList;

	Fonts();
	~Fonts();

public:
	static Fonts* getInstance();
	static Fonts* destruction();
	
	TTF_Font* getTTF_Font(string& type, int& taille);

};


class Texte
{
	TTF_Font* font;
	SDL_Surface* surface;

public:
	Texte(string& typeFont, int& taille, string& message, SDL_Color& couleur, int largeur=0, int hauteur=0);
	~Texte();

	SDL_Surface* getSurface();
	void setSurface(SDL_Surface* surface);
};