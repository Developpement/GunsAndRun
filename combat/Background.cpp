
#include "Background.h"



Background::Background(int &posX, int &posY, Configuration *config, Surfaces *surfaces, Application* application)
{
	this->config = config;
	this->surfaces = surfaces;
	this->application = application;
	load();

	posXbackground = static_cast<float>(-posX);
	posYbackground = static_cast<float>(-posY);

	velXbackgroundTeo=velXbackground=velYbackground=velYbackgroundTeo=0;
	
	maxSpeed = stringToFloat( this->config->getValeurParametre("playerMaxSpeed") );
}

int Background::load()
{
	animation = surfaces->getAnimation("backgroundVisible");
	imageCourante=(*animation).begin();
	boitesCollisions = surfaces->getBoitesCollisions("backgroundVisible");

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
				cout << "collision" << endl;		
				return true;
			}
			return false;
		}//end if PJ_JOUABLE
		itUnite++;
	}

	return false;
}

int Background::handleInput(SDL_Event &event)
{
	//// Détection collision avec le joueur? Alors on ne se déplace pas.
	//if(this->application->keyValue.isArrowDownPressed)
	//	velYbackground=-maxSpeed;
	//else if (this->application->keyValue.isArrowUpPressed)
	//	velYbackground=maxSpeed;
	//else velYbackground=0;
	//
	//if(this->application->keyValue.isArrowLeftPressed)
	//	velXbackground=maxSpeed;
	//else if(this->application->keyValue.isArrowRightPressed)
	//	velXbackground=-maxSpeed;
	//else velXbackground=0;

	//if ((velXbackground!=0)&&(velYbackground!=0)){ // diagonale
	//	if((velXbackground==maxSpeed)||(velXbackground==-maxSpeed)){
	//		velXbackground=velXbackground/coeffSpeedDiago;
	//		velYbackground=velYbackground/coeffSpeedDiago;
	//	}
	//}
	//
	//if (velXbackground != 0) {
	//	if ( detecteCollisions(static_cast<int>(velXbackground), zero)== true) {
	//		velXbackground*=-1;
	//		/*if(velXbackground>0)
	//			posXbackground-=maxSpeed;
	//		else posXbackground+=maxSpeed;
	//		velXbackground = 0;	*/
	//	}
	//}
	//if (velYbackground != 0) {
	//	if ( detecteCollisions(zero, static_cast<int>(velYbackground))== true) {
	//		velYbackground*=-1;
	//		/*if(velYbackground>0)
	//			posYbackground-=maxSpeed;
	//		else posYbackground+=maxSpeed;
	//		velYbackground = 0;*/
	//	}
	//}

	/*
	switch (event.type) {
		//Si une touche a ete pressee
		case SDL_KEYDOWN:
			//ajustement de la vitesse
			switch( event.key.keysym.sym )
			{
				case SDLK_UP: velYbackground += maxSpeed; break;
				case SDLK_DOWN: velYbackground -= 1; break;
				case SDLK_LEFT: velXbackground += 1; break;
				case SDLK_RIGHT: velXbackground -= 1; break;
				default: break;
			}

			break;
		//Si une touche a ete relachee
		case SDL_KEYUP:
			//ajustement de la vitesse
			switch( event.key.keysym.sym )
			{
				case SDLK_UP: velYbackground = 0; break;
				case SDLK_DOWN: velYbackground = 0; break;
				case SDLK_LEFT: velXbackground = 0; break;
				case SDLK_RIGHT: velXbackground = 0; break;
				default: break;
			}
			break;
	}
	*/

	return 0;
}



int Background::setSpeedKeyUpPressed()
{
	if(velXbackgroundTeo==0){
		velYbackgroundTeo=maxSpeed;
	}
	else {
		if(abs(velXbackgroundTeo)==maxSpeed){
			velXbackgroundTeo/=coeffSpeedDiago;
			velYbackgroundTeo=maxSpeed/coeffSpeedDiago;
		}
	}
	return 0;
}
int Background::setSpeedKeyDownPressed()
{
	if(velXbackgroundTeo==0){
		velYbackgroundTeo=-maxSpeed;
	}
	else {
		if(abs(velXbackgroundTeo)==maxSpeed){
			velXbackgroundTeo/=coeffSpeedDiago;
			velYbackgroundTeo=-maxSpeed/coeffSpeedDiago;
		}
	}
	return 0;
}

int Background::setSpeedKeyRightPressed()
{
	if(velYbackgroundTeo==0) {
		velXbackgroundTeo=-maxSpeed;
	}
	else {
		if(abs(velYbackgroundTeo)==maxSpeed){
			velXbackgroundTeo=-maxSpeed/coeffSpeedDiago;
			velYbackgroundTeo/=coeffSpeedDiago;
		}
	}
	return 0;
}

int Background::setSpeedKeyLeftPressed()
{
	if(velYbackgroundTeo==0) {
		velXbackgroundTeo=maxSpeed;
	}
	else {
		if(abs(velYbackgroundTeo)==maxSpeed){
			velXbackgroundTeo=maxSpeed/coeffSpeedDiago;
			velYbackgroundTeo/=coeffSpeedDiago;
		}
	}
	return 0;
}


int Background::setSpeedKeyUpReleased()
{
	velYbackgroundTeo=0;
	float speedLimit=maxSpeed/coeffSpeedDiago;
	if(velXbackgroundTeo!=0) {
		if(velXbackgroundTeo<0)
			velXbackgroundTeo=-maxSpeed;
		else velXbackgroundTeo=maxSpeed;
	}

	return 0;
}
int Background::setSpeedKeyDownReleased()
{
	velYbackgroundTeo=0;
	float speedLimit=maxSpeed/coeffSpeedDiago;
	if(velXbackgroundTeo!=0) {
		if(velXbackgroundTeo<0)
			velXbackgroundTeo=-maxSpeed;
		else velXbackgroundTeo=maxSpeed;
	}
	return 0;
}
int Background::setSpeedKeyRightReleased()
{
	velXbackgroundTeo=0;
	float speedLimit=maxSpeed/coeffSpeedDiago;
	if(velYbackgroundTeo!=0) {
		if(velYbackgroundTeo<0)
			velYbackgroundTeo=-maxSpeed;
		else velYbackgroundTeo=maxSpeed;
	}
	return 0;
}
int Background::setSpeedKeyLeftReleased()
{
	velXbackgroundTeo=0;
	float speedLimit=maxSpeed/coeffSpeedDiago;
	if(velYbackgroundTeo!=0) {
		if(velYbackgroundTeo<0)
			velYbackgroundTeo=-maxSpeed;
		else velYbackgroundTeo=maxSpeed;
	}

	return 0;
}

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
	afficheEcran(static_cast<int>(posXbackground), static_cast<int>(posYbackground), screen, *imageCourante);

	return 0;
}