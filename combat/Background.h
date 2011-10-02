#pragma once

#include "Application.h"
#include "DisplayFormatSurfaces.h"
#include "Configuration.h"
#include "Affichage.h"
#include "Outils.h"
#include <cmath>
#include <SDL.h>
#include <vector>
#include <map>
using namespace std;

static float zero = 0;
static float coeffSpeedDiago=1.4f;

class Application;

class Background 
{
public:	
	Application* application;
	Configuration* config;
	Surfaces* surfaces;

	float maxSpeed; // vitesse max sur le plan de déplacement

	vector<SDL_Surface*>* animation;
	vector<SDL_Surface*>::iterator imageCourante;
	vector<SDL_Rect>* boitesCollisions;

	// position des decors, directement liés à la vitesse de déplacement du joueur
	float posXbackground, posYbackground, velXbackground, velYbackground, velXbackgroundTeo, velYbackgroundTeo;
	
	Background(int& posX, int& posY, Configuration*, Surfaces*, Application*);
	bool detecteCollisions(float& decalX, float& decalY);
	int load();
	int update();
	int handleInput(SDL_Event& event);
	int setSpeedKeyUpPressed();
	int setSpeedKeyDownPressed();
	int setSpeedKeyRightPressed();
	int setSpeedKeyLeftPressed();

	int setSpeedKeyUpReleased();
	int setSpeedKeyDownReleased();
	int setSpeedKeyRightReleased();
	int setSpeedKeyLeftReleased();

	int draw(SDL_Surface* screen);
};