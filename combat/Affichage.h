#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <algorithm>

/**
* \brief Convertit une suface donn�e en une nouvelle surface affichable.
* \param surface SDL_Surface � convertir.
* \param conserveOriginal true si l'ancienne surface doit �tre conserv�e, false sinon.
* \return Nouvelle surface affichable.
*/
SDL_Surface* conversionFormatAffichable(SDL_Surface* surface, bool conserveOriginal = true);

/**
* \brief Redimmentionne une surface en modifiant sa largeur et sa hauteur.
* \details Une nouvelle surface est cr��e et remplace l'ancienne. La nouvelle surface est une copie redimentionn�e de l'ancienne surface, conservant le ratio ou non.
* \param surfaceCourante La surface � transformer.
* \param largeur Largeur souhait�e de la nouvelle surface.
* \param hauteur Hauteur souhait�e de la nouvelle surface.
* \param conserveProportions true si le redimentionnement conserve le ratio, l'image cible ne pouvant exc�der la taille demand�e.
* \return La nouvelle surface redimentionn�e.
*/
SDL_Surface* redimensionneSurface (SDL_Surface* surfaceCourante, int& largeur, int& hauteur, bool conserveProportions = true);

/**
* \brief Effectue une rotation sur l'image courante.
* \param surfaceCourante SDL_surface � pivoter.
* \param angle L'angle de rotation.
* \conserveOriginal true si l'image courante doit �tre conserv�e, false si la m�moire doit �tre lib�r�e.
* \return La nouvelle surface pivot�e.
*/
SDL_Surface* pivoteSurface (SDL_Surface* surfaceCourante, double angle, bool conserveOriginal = true);

#if 0
/**
* \brief Charge en m�moire une image au format Bitmap.
* \param nomFichier nom du fichier de l'image � charger.
* \return La structure contenant l'image pouvant �tre affich�e � l'�cran.
*/
SDL_Surface* chargeBMPFormatAffichable (const char* nomFichier);

/**
* \brief Charge en m�moire une image au format Bitmap et la redimentionne.
* \param nomFichier Nom du fichier de l'image � charger puis retravailler.
* \param largeur Largeur souhait�e de l'image cible.
* \param hauteur Hauteur souhait�e de l'image cible.
* \param angle Angle souhait�e de l'image cible.
* \return La surface charg�e et redimmentionn�e.
*/
SDL_Surface* chargeBMPFormatAffichable (const char* nomFichier, int largeur, int hauteur, double angle, bool conserveProportions = true);


/**
* \brief Affiche une surface � l'�cran en effectuant le redimmentionnement, la rotation, puis la copie d'une SDL_Surface sur une autre (�cran).
* \param ecran Surface de destination.
* \param src Surface source.
* \param largeur Largeur de la surface src affich�e � l'�cran.
* \param hauteur Hauteur de la surface src affich�e � l'�cran.
* \param angle Angle de la surface src affich�e � l'�cran.
*/
void afficheEcran(SDL_Surface* ecran, SDL_Surface* src, int& largeur, int& hauteur, double& angle);



/**
* \brief Affiche une surface � l'�cran en effectuant le redimentionnement, puis la copie d'une SDL_Surface source sur une autre (�cran).
* \param ecran Surface de destination.
* \param src Surface source.
* \param angle Angle de la surface src affich�e � l'�cran.
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
