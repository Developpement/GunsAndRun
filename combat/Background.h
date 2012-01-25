#pragma once

#include "Gestionnaire.h"
#include "DisplayFormatSurfaces.h"
#include "ConfigurationJeu.h"
#include "Affichage.h"
#include "Outils.h"
#include "Debug.h"
#include "Clavier.h"
#include "Direction.h"
#include <cmath>
#include <SDL/SDL.h>
#include <vector>
#include <map>
using namespace std;



class Gestionnaire;

class Background
{
	static Background* _singleton;

	Background();
	~Background();

public:
	Gestionnaire* application;
	ConfigurationJeu* config;
	Surfaces* surfaces;
	Debug* debug;

	float maxSpeed; // vitesse max sur le plan de déplacement

	vector<SDL_Surface*>* fondNoir;
	vector<SDL_Surface*>* animation;
	vector<SDL_Surface*>::iterator imageCourante;
	vector<SDL_Rect>* boitesCollisions; 

	string nomMap;

	// position des decors, directement liés à la vitesse de déplacement du joueur
	float posXbackground;
	float posYbackground;
	float velXbackground;
	float velYbackground;
	float velXbackgroundTeo;
	float velYbackgroundTeo;

//	Background(int& posX, int& posY, string& map);
	bool detecteCollisions(float& decalX, float& decalY);
	int load();
	int update();
	void setDirection();
	//int handleInput(SDL_Event& event);
	/*int setSpeedKeyUpPressed();
	int setSpeedKeyDownPressed();
	int setSpeedKeyRightPressed();
	int setSpeedKeyLeftPressed();

	int setSpeedKeyUpReleased();
	int setSpeedKeyDownReleased();
	int setSpeedKeyRightReleased();
	int setSpeedKeyLeftReleased();*/

	int draw(SDL_Surface* screen);

	
	static Background* getInstance();
	//static Background* initInstance(int& posX, int& posY, string& map);
	static Background* destruction();
};
