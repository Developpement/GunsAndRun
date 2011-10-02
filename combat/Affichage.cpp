
#include "Affichage.h"

/**
* \brief Convertit une suface donnée en une nouvelle surface affichable.
* \param surface SDL_Surface à convertir.
* \param conserveOriginal true si l'ancienne surface doit être conservée, false sinon.
* \return Nouvelle surface affichable.
*/
SDL_Surface* conversionFormatAffichable(SDL_Surface* surfaceCourante, bool conserveOriginal)
{
	SDL_Surface* nouvelleSurface = SDL_DisplayFormat(surfaceCourante);
	if (conserveOriginal == false)
		SDL_FreeSurface(surfaceCourante);
	return nouvelleSurface;
}

/**
* \brief Redimmentionne une surface en modifiant sa largeur et sa hauteur.
* \details Une nouvelle surface est créée et remplace l'ancienne. La nouvelle surface est une copie redimentionnée de l'ancienne surface, conservant le ratio ou non.
* \param surfaceCourante La surface à transformer.
* \param largeur Largeur souhaitée de la nouvelle surface.
* \param hauteur Hauteur souhaitée de la nouvelle surface.
* \param conserveRation true si le redimentionnement conserve le ratio, l'image cible ne pouvant excéder la taille demandée.
* \return La nouvelle surface redimentionnée.
*/
SDL_Surface* redimensionneSurface (SDL_Surface* surfaceCourante, int& largeur, int& hauteur, bool conserveProportions)
{
	SDL_Surface* nouvelleSurface;
	double zoomLargeur = ((double)largeur)/surfaceCourante->w;
	double zoomHauteur = ((double)hauteur)/surfaceCourante->h;
	if (conserveProportions) {
		double zoom = std::min(zoomLargeur, zoomHauteur);
		nouvelleSurface = rotozoomSurface (surfaceCourante, 0, zoom,0);
	}
	else {
		nouvelleSurface = rotozoomSurfaceXY  (surfaceCourante,0, zoomLargeur, zoomHauteur, 0);
	}
	SDL_FreeSurface(surfaceCourante);
	

	nouvelleSurface = conversionFormatAffichable(nouvelleSurface, false);
	Uint32 colorkey = SDL_MapRGB( nouvelleSurface->format, 0, 0xFF, 0xFF ); 
	SDL_SetColorKey( nouvelleSurface, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey );

	return nouvelleSurface;
}

/**
* \brief Effectue une rotation sur l'image courante.
* \param surfaceCourante SDL_surface à transformer.
* \param angle L'angle de rotation.
* \conserveOriginal true si l'image courante doit être conservée, false si la mémoire doit être libérée.
* \return La nouvelle surface transformée.
*/
SDL_Surface* pivoteSurface (SDL_Surface* surfaceCourante, double angle, bool conserveOriginal)
{
	SDL_Surface* nouvelleSurface = rotozoomSurface (surfaceCourante, angle, 1, 0);
	if (conserveOriginal == false)
		SDL_FreeSurface(surfaceCourante);
	return nouvelleSurface;
}

#if 0
/**
* \brief Charge en mémoire une image au format Bitmap.
* \param nomFichier nom du fichier de l'image à charger.
* \return La structure contenant l'image pouvant être affichée à l'écran.
*/
SDL_Surface* chargeBMPFormatAffichable (const char* nomFichier)
{
	/* convert bitmap to display format */
	SDL_Surface* surfaceBrute = SDL_LoadBMP(nomFichier); 
	SDL_Surface* nouvelleSurface = SDL_DisplayFormat(surfaceBrute);
	SDL_FreeSurface(surfaceBrute);
	return nouvelleSurface;
}

/**
* \brief Charge en mémoire une image au format Bitmap et la redimentionne.
* \param nomFichier Nom du fichier de l'image à charger puis retravailler.
* \param largeur Largeur souhaitée de l'image cible.
* \param hauteur Hauteur souhaitée de l'image cible.
* \param angle Angle souhaitée de l'image cible.
* \return La surface chargée et redimmentionnée.
*/
SDL_Surface* chargeBMPFormatAffichable (const char* nomFichier, int largeur, int hauteur, double angle, bool conserveProportions)
{
	SDL_Surface* nouvelleSurface = SDL_LoadBMP(nomFichier);
	if(nouvelleSurface==0)
		return 0;

	nouvelleSurface = pivoteSurface(nouvelleSurface,angle,false);
	nouvelleSurface = redimensionneSurface(nouvelleSurface, largeur, hauteur, conserveProportions);
	return conversionFormatAffichable(nouvelleSurface,false);
}

/**
* \brief Affiche une surface à l'écran en effectuant la copie d'une SDL_Surface sur une autre (écran).
* \param ecran Surface de destination.
* \param src Surface source.
* \param largeur Largeur de la surface src affichée à l'écran.
* \param hauteur Hauteur de la surface src affichée à l'écran.
* \param angle Angle de la surface src affichée à l'écran.
*/
void afficheEcran(SDL_Surface* ecran, SDL_Surface* source, int& largeur, int& hauteur, double& angle)
{
	SDL_Surface* surfaceAfficher = pivoteSurface(source,angle);
	if ((largeur != surfaceAfficher->w) || (hauteur != surfaceAfficher->h))
		surfaceAfficher = redimensionneSurface(surfaceAfficher,largeur, hauteur, true);

	SDL_BlitSurface(surfaceAfficher, NULL, ecran, NULL);
	SDL_FreeSurface(surfaceAfficher);
}

/**
* \brief Affiche une surface à l'écran en effectuant le redimentionnement, puis la copie d'une SDL_Surface source sur une autre (écran).
* \param ecran Surface de destination.
* \param src Surface source.
* \param angle Angle de la surface src affichée à l'écran.
*/
void afficheEcran(SDL_Surface* ecran, SDL_Surface* source, double& angle)
{
	SDL_Surface* surfaceAfficher = pivoteSurface(source,angle);
	SDL_BlitSurface(surfaceAfficher, NULL, ecran, NULL);
	SDL_FreeSurface(surfaceAfficher);
}
#endif
