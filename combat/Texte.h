#pragma once

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

static string CASLONBOLD="CaslonBold.ttf"	;

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
	SDL_Surface* message;
public:
	Texte(string& typeFont, int& taille, string& message, SDL_Color& couleur);
	~Texte();

	SDL_Surface* getSurface();

};