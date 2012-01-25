#include "Background.h"


Background* Background::_singleton = 0;

static float zero = 0;
//static float coeffSpeedDiago=1.4f;
static float coeffSpeedDiago=0.7f;


Background::~Background()
{
	debug->print("Background destructeur appele");

}

Background::Background()
{
	debug=Debug::getInstance();
	config=ConfigurationJeu::getInstance();
	surfaces=Surfaces::getInstance();
	application=Gestionnaire::getInstance();
	nomMap=nomMap=config->getValeurParametre("map");
	load();

	posXbackground = -stringToFloat(config->getValeurParametre("joueurJouable.posX"));
	posYbackground = -stringToFloat(config->getValeurParametre("joueurJouable.posY"));

	velXbackgroundTeo=velXbackground=velYbackground=velYbackgroundTeo=0;
	string playerStartSpeed = config->getValeurParametre("joueurJouable.StartSpeed");
	maxSpeed = stringToFloat(playerStartSpeed);
}

int Background::load()
{
	string windowWidthStr= config->getValeurParametre("ScreenWidth");
	string windowHeightStr= config->getValeurParametre("ScreenHeight");
	int windowWidth=stringToInt(windowWidthStr);
	int windowHeight=stringToInt(windowHeightStr);

	animation = surfaces->getAnimation("map");
	imageCourante=(*animation).begin();
	boitesCollisions = surfaces->getBoitesCollisions("map");

	fondNoir = surfaces->getAnimation("ecranNoir", windowWidth, windowHeight);
	return 0;
}
/*
*\brief détection des collisions avec d'autre objets.
*\param decalX décalage horizontal en pixels.
*\param decalY décalage vertical en pixels.
*\return true si une collision a été détecté, false dans l'autre cas.
*/
bool Background::detecteCollisions(float& decalX, float& decalY)
{
	// détection background unitees;
	list<Unite*>::iterator itUnite = application->unitees.begin();
	while (itUnite != application->unitees.end()) {
		if ((*itUnite)->typeUnite==PJOUEUR_JOUABLE){
			float newX = posXbackground + decalX;
			float newY = posYbackground + decalY;

			if (collision(newX, newY, *boitesCollisions, (*itUnite)->posX, (*itUnite)->posY, *(*itUnite)->boitesCollisions) == true) {
				debug->print("collision");
				return true;
			}
			return false;
		}//end if PJ_JOUABLE
		itUnite++;
	}

	return false;
}

void Background::setDirection()
{
	Clavier* clavier=Clavier::getInstance();
	int direction=DIRECTION_TOUTES;

	if(!(clavier->etatClavier&FLECHE_BAS_PRESSEE)) {
		direction&=~DIRECTION_BAS;
	}
	else if(clavier->etatClavier&FLECHE_HAUT_PRESSEE) {
		direction&=~DIRECTION_BAS;
		direction&=~DIRECTION_HAUT;
	}

	if(!(clavier->etatClavier&FLECHE_DROITE_PRESSEE))
		direction&=~DIRECTION_DROITE;
	else if(clavier->etatClavier&FLECHE_GAUCHE_PRESSEE) {
		direction&=~DIRECTION_GAUCHE;
		direction&=~DIRECTION_DROITE;
	}

	if(!(clavier->etatClavier&FLECHE_GAUCHE_PRESSEE))
		direction&=~DIRECTION_GAUCHE;
	if(!(clavier->etatClavier&FLECHE_HAUT_PRESSEE))
		direction&=~DIRECTION_HAUT;


	switch(direction) {
		case DIRECTION_HAUT:
			velYbackgroundTeo=maxSpeed;
			velXbackgroundTeo=0;
			break;
		case DIRECTION_HAUT_DROITE:
			velXbackgroundTeo=-maxSpeed*coeffSpeedDiago;
			velYbackgroundTeo=maxSpeed*coeffSpeedDiago;
			break;
		case DIRECTION_DROITE:
			velXbackgroundTeo=-maxSpeed;
			velYbackgroundTeo=0;
			break;
		case DIRECTION_DROITE_BAS:
			velXbackgroundTeo=-maxSpeed*coeffSpeedDiago;
			velYbackgroundTeo=-maxSpeed*coeffSpeedDiago;
			break;
		case DIRECTION_BAS:
			velXbackgroundTeo=0;
			velYbackgroundTeo=-maxSpeed;
			break;
		case DIRECTION_BAS_GAUCHE:
			velXbackgroundTeo=maxSpeed*coeffSpeedDiago;
			velYbackgroundTeo=-maxSpeed*coeffSpeedDiago;
			break;
		case DIRECTION_GAUCHE:
			velXbackgroundTeo=maxSpeed;
			velYbackgroundTeo=0;
			break;
		case DIRECTION_GAUCHE_HAUT:
			velXbackgroundTeo=maxSpeed*coeffSpeedDiago;
			velYbackgroundTeo=maxSpeed*coeffSpeedDiago;
			break;
		case DIRECTION_AUCUNE:
			velXbackgroundTeo=0;
			velYbackgroundTeo=0;
			break;
	}
}



//
//int Background::setSpeedKeyUpPressed()
//{
//	if(velXbackgroundTeo==0){
//		velYbackgroundTeo=maxSpeed;
//	}
//	else {
//		if(abs(velXbackgroundTeo)==maxSpeed){
//			velXbackgroundTeo/=coeffSpeedDiago;
//			velYbackgroundTeo=maxSpeed/coeffSpeedDiago;
//		}
//	}
//	return 0;
//}
//int Background::setSpeedKeyDownPressed()
//{
//	if(velXbackgroundTeo==0){
//		velYbackgroundTeo=-maxSpeed;
//	}
//	else {
//		if(abs(velXbackgroundTeo)==maxSpeed){
//			velXbackgroundTeo/=coeffSpeedDiago;
//			velYbackgroundTeo=-maxSpeed/coeffSpeedDiago;
//		}
//	}
//	return 0;
//}
//
//int Background::setSpeedKeyRightPressed()
//{
//	if(velYbackgroundTeo==0) {
//		velXbackgroundTeo=-maxSpeed;
//	}
//	else {
//		if(abs(velYbackgroundTeo)==maxSpeed){
//			velXbackgroundTeo=-maxSpeed/coeffSpeedDiago;
//			velYbackgroundTeo/=coeffSpeedDiago;
//		}
//	}
//	return 0;
//}
//
//int Background::setSpeedKeyLeftPressed()
//{
//	if(velYbackgroundTeo==0) {
//		velXbackgroundTeo=maxSpeed;
//	}
//	else {
//		if(abs(velYbackgroundTeo)==maxSpeed){
//			velXbackgroundTeo=maxSpeed/coeffSpeedDiago;
//			velYbackgroundTeo/=coeffSpeedDiago;
//		}
//	}
//	return 0;
//}
//
//
//int Background::setSpeedKeyUpReleased()
//{
//	velYbackgroundTeo=0;
////	float speedLimit=maxSpeed/coeffSpeedDiago;
//	if(velXbackgroundTeo!=0) {
//		if(velXbackgroundTeo<0)
//			velXbackgroundTeo=-maxSpeed;
//		else velXbackgroundTeo=maxSpeed;
//	}
//
//	return 0;
//}
//int Background::setSpeedKeyDownReleased()
//{
//	velYbackgroundTeo=0;
////	float speedLimit=maxSpeed/coeffSpeedDiago;
//	if(velXbackgroundTeo!=0) {
//		if(velXbackgroundTeo<0)
//			velXbackgroundTeo=-maxSpeed;
//		else velXbackgroundTeo=maxSpeed;
//	}
//	return 0;
//}
//int Background::setSpeedKeyRightReleased()
//{
//	velXbackgroundTeo=0;
////	float speedLimit=maxSpeed/coeffSpeedDiago;
//	if(velYbackgroundTeo!=0) {
//		if(velYbackgroundTeo<0)
//			velYbackgroundTeo=-maxSpeed;
//		else velYbackgroundTeo=maxSpeed;
//	}
//	return 0;
//}
//int Background::setSpeedKeyLeftReleased()
//{
//	velXbackgroundTeo=0;
////	float speedLimit=maxSpeed/coeffSpeedDiago;
//	if(velYbackgroundTeo!=0) {
//		if(velYbackgroundTeo<0)
//			velYbackgroundTeo=-maxSpeed;
//		else velYbackgroundTeo=maxSpeed;
//	}
//
//	return 0;
//}

int Background::update()
{
	if (velXbackgroundTeo != 0) {
		if ( detecteCollisions(velXbackgroundTeo, zero)== true) {
			velXbackground=0;
		}
		else velXbackground=velXbackgroundTeo;
	}
	else velXbackground=velXbackgroundTeo;


	if (velYbackgroundTeo != 0) {
		if ( detecteCollisions(zero, velYbackgroundTeo)== true) {
			velYbackground=0;
		}
		else velYbackground=velYbackgroundTeo;
	}
	else velYbackground=velYbackgroundTeo;

	posXbackground += velXbackground;
	posYbackground += velYbackground;

	return 0;
}


int Background::draw(SDL_Surface *screen)
{
	afficheEcran(zero,zero, screen, fondNoir->at(0));
	afficheEcran(static_cast<int>(posXbackground), static_cast<int>(posYbackground), screen, *imageCourante);

	return 0;
}

//
//Background* Background::initInstance(int& posX, int& posY, string& map)
//{
//	if(_singleton==0) 
//		_singleton=new Background(posX, posY, map);
//	return _singleton;
//}


Background* Background::getInstance()
{
	if(_singleton==0)
		_singleton=new Background();
	return _singleton;
}

Background* Background::destruction()
{
	if(_singleton!=0){
		delete _singleton;
		_singleton=0;
	}
	return _singleton;
}