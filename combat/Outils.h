#pragma once

#include <SDL/SDL.h>
#include <vector>
using namespace std;


#define PI 3.14

vector<SDL_Rect> obtienRectCollisionSurface (SDL_Surface* surface);


double calculAngle (int& x1, int& y1, int& x2, int& y2);


/*
	SDL bounding box collision tests (works on SDL_Rect's)
*/
inline int SDL_CollideBoundingBox(SDL_Rect& a , SDL_Rect& b)
{
	if(b.x + b.w < a.x)	return 0;	//just checking if their
	if(b.x > a.x + a.w)	return 0;	//bounding boxes even touch

	if(b.y + b.h < a.y)	return 0;
	if(b.y > a.y + a.h)	return 0;

	return 1;				//bounding boxes intersect
}


template <typename A, typename B, typename C, typename D>
bool collision(A& pos1X, B& pos1Y, vector<SDL_Rect>& boitesCollision1,
			   C& pos2X, D& pos2Y, vector<SDL_Rect>& boitesCollision2)
{
	SDL_Rect rect1, rect2;

	for (vector<SDL_Rect>::iterator it1 = boitesCollision1.begin(); it1 != boitesCollision1.end(); it1++) {
		for (vector<SDL_Rect>::iterator it2 = boitesCollision2.begin(); it2 != boitesCollision2.end(); it2++) {
			rect1 = *it1;
			rect2 = *it2;

			rect1.x += static_cast<Sint16>(pos1X);
			rect1.y += static_cast<Sint16>(pos1Y);
			rect2.x += static_cast<Sint16>(pos2X);
			rect2.y += static_cast<Sint16>(pos2Y);

			if (SDL_CollideBoundingBox(rect1,rect2) !=0)
				return true;
		}
	}
	return false;
}


float angleVersX (float& vitesse, double& angle);
float angleVersY (float& vitesse, double& angle);
bool collision(int& pointX, int& pointY, int& boitesX, int& boitesY, vector<SDL_Rect>& boitesCollision);


SDL_Surface* insertDelimiteurSurface(SDL_Surface* surface, int largeur);