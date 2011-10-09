#pragma once

#include "Application.h"
#include "DisplayFormatSurfaces.h"
#include "Configuration.h"
#include "Affichage.h"
#include "Outils.h"
#include <cmath>
#include <SDL/SDL.h>
#include <vector>
#include <map>
using namespace std;



class Application;

class Background
{
public:
	Application* application;
	Configuration* config;
	Surfaces* surfaces;

	float maxSpeed; // vitesse max sur le plan de d�placement

	vector<SDL_Surface*>* animation;
	vector<SDL_Surface*>::iterator imageCourante;
	vector<SDL_Rect>* boitesCollisions;

	// position des decors, directement li�s � la vitesse de d�placement du joueur
	float posXbackground;
	float posYbackground;
	float velXbackground;
	float velYbackground;
	float velXbackgroundTeo;
	float velYbackgroundTeo;

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
