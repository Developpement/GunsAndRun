
#include "Outils.h"
#include <math.h>


Uint32 getPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}




void agrandiRectangle (vector<SDL_Rect>& out, SDL_Rect& nouveauRectangle) 
{
	bool found = false;

	vector<SDL_Rect>::iterator it;
	for (it = out.begin(); it != out.end(); it++) {
		if ((nouveauRectangle.x == it->x) && (nouveauRectangle.w == it->w) && (nouveauRectangle.y == it->y + it->h)) {
			found = true;
			it->h++;
		}
	}
	if (found == false) {
		out.push_back(nouveauRectangle);
	}
}


SDL_Surface* insertDelimiteurSurface(SDL_Surface* surface, int largeur)
{
	SDL_Rect rectangle1, rectangle2;
	rectangle1.x = rectangle1.y = 0;
	rectangle2.x = surface->w - largeur;
	rectangle2.y = surface->h - largeur;
	rectangle1.w = rectangle1.h = rectangle2.w = rectangle2.h = largeur;

	Uint32 couleur = SDL_MapRGB(surface->format, 0, 0, 0);

	SDL_FillRect(surface, &rectangle1, couleur);
	SDL_FillRect(surface, &rectangle2, couleur);
	return surface;
}



vector<SDL_Rect> obtienRectCollisionSurface (SDL_Surface* surface)
{
	vector<SDL_Rect> out;
	//vector<SDL_Rect>::iterator it;
	SDL_Rect nouveauRectange;
	Uint8 r, g, b;
	bool estCyan = false;

	for(int y = 0; y < surface->h; y++) {
		if (estCyan == true) { // fin de ligne
			estCyan = false;
			nouveauRectange.w = surface->w -nouveauRectange.x;
			//Ajout du nouveauRectangle dans le vecteur.
			agrandiRectangle(out,nouveauRectange);
		}

		for(int x = 0; x < surface->w; x++) {
			Uint32 pos = getPixel(surface,x, y);
			SDL_GetRGB(pos, surface->format, &r, &g, &b);
			if ((r==0x00)&&(g==0xFF)&&(b==0xFF)) {
				if(estCyan == false) { // début du rectangle
					estCyan = true;
					nouveauRectange.x = x;
					nouveauRectange.y = y;
					nouveauRectange.h = 1;
				}
			}
			else {
				if (estCyan == true) { // fin du rectangle
					estCyan = false;
					// Ajout du rectangle
					nouveauRectange.w = x-nouveauRectange.x;
					agrandiRectangle(out,nouveauRectange);
				}
			}
		}
	}
	return out;
}





double calculAngle (int& x1, int& y1, int& x2, int& y2)
{
	float hauteur = (float)y1-y2; //(float) abs(y2-y1);
	float largeur = (float)x2-x1;//(float) abs(x2-x1);
	double angle;

	if (x2 >= x1)
		angle = (double) (atan(hauteur/largeur)*180/3.14);
	else {
		angle = (double) (atan(hauteur/largeur)*180/3.14) + 180;
	}
	return angle;
}

float angleVersX (float& vitesse, double& angle)
{
	return vitesse*(float)cos(angle*PI/180);
}
float angleVersY (float& vitesse, double& angle)
{
	return -vitesse*(float)sin(angle*PI/180);
}


bool collision(int& pointX, int& pointY, int& boitesX, int& boitesY, vector<SDL_Rect>& boitesCollision)
{
	SDL_Rect rect1, rect2;
	rect1.x=pointX;
	rect1.y=pointY;
	rect1.w=1;
	rect1.h=1;


	for(vector<SDL_Rect>::iterator it=boitesCollision.begin();it!=boitesCollision.end();it++){
		rect2=*it;
		rect2.x=boitesX;
		rect2.y=boitesY;
		if (SDL_CollideBoundingBox(rect1,rect2) !=0)
			return true;
	}
	return false;
}




