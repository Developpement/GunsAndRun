#pragma once

#include <SDL.h>
#include <SDL_rotozoom.h>
#include <algorithm>

/**
* \brief Convertit une suface donnée en une nouvelle surface affichable.
* \param surface SDL_Surface à convertir.
* \param conserveOriginal true si l'ancienne surface doit être conservée, false sinon.
* \return Nouvelle surface affichable.
*/
SDL_Surface* conversionFormatAffichable(SDL_Surface* surface, bool conserveOriginal = true);

/**
* \brief Redimmentionne une surface en modifiant sa largeur et sa hauteur.
* \details Une nouvelle surface est créée et remplace l'ancienne. La nouvelle surface est une copie redimentionnée de l'ancienne surface, conservant le ratio ou non.
* \param surfaceCourante La surface à transformer.
* \param largeur Largeur souhaitée de la nouvelle surface.
* \param hauteur Hauteur souhaitée de la nouvelle surface.
* \param conserveProportions true si le redimentionnement conserve le ratio, l'image cible ne pouvant excéder la taille demandée.
* \return La nouvelle surface redimentionnée.
*/
SDL_Surface* redimensionneSurface (SDL_Surface* surfaceCourante, int& largeur, int& hauteur, bool conserveProportions = true);

/**
* \brief Effectue une rotation sur l'image courante.
* \param surfaceCourante SDL_surface à pivoter.
* \param angle L'angle de rotation.
* \conserveOriginal true si l'image courante doit être conservée, false si la mémoire doit être libérée.
* \return La nouvelle surface pivotée.
*/
SDL_Surface* pivoteSurface (SDL_Surface* surfaceCourante, double angle, bool conserveOriginal = true);

#if 0
/**
* \brief Charge en mémoire une image au format Bitmap.
* \param nomFichier nom du fichier de l'image à charger.
* \return La structure contenant l'image pouvant être affichée à l'écran.
*/
SDL_Surface* chargeBMPFormatAffichable (const char* nomFichier);

/**
* \brief Charge en mémoire une image au format Bitmap et la redimentionne.
* \param nomFichier Nom du fichier de l'image à charger puis retravailler.
* \param largeur Largeur souhaitée de l'image cible.
* \param hauteur Hauteur souhaitée de l'image cible.
* \param angle Angle souhaitée de l'image cible.
* \return La surface chargée et redimmentionnée.
*/
SDL_Surface* chargeBMPFormatAffichable (const char* nomFichier, int largeur, int hauteur, double angle, bool conserveProportions = true);


/**
* \brief Affiche une surface à l'écran en effectuant le redimmentionnement, la rotation, puis la copie d'une SDL_Surface sur une autre (écran). 
* \param ecran Surface de destination.
* \param src Surface source.
* \param largeur Largeur de la surface src affichée à l'écran.
* \param hauteur Hauteur de la surface src affichée à l'écran.
* \param angle Angle de la surface src affichée à l'écran.
*/
void afficheEcran(SDL_Surface* ecran, SDL_Surface* src, int& largeur, int& hauteur, double& angle);



/**
* \brief Affiche une surface à l'écran en effectuant le redimentionnement, puis la copie d'une SDL_Surface source sur une autre (écran).
* \param ecran Surface de destination.
* \param src Surface source.
* \param angle Angle de la surface src affichée à l'écran.
*/
void afficheEcran(SDL_Surface* ecran, SDL_Surface* src, double& angle);
#endif

//-----------------------------------------------------------------------------------------------------------------------------------------
template <typename T>
inline void afficheEcran(T x, T y, SDL_Surface* ecran, SDL_Surface* surface)
{
	//rectangle temporaire
    SDL_Rect offset;

    offset.x = static_cast<Sint16>(x);
    offset.y = static_cast<Sint16>(y);

    //on blit la surface
    SDL_BlitSurface( surface, NULL, ecran, &offset );
}