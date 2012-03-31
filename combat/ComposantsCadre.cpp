#include "ComposantsCadre.h"
#include "Form_menu.h"



ComposantCadre::ComposantCadre()
{
	debug=Debug::getInstance();
	this->application=0;
	debug->print("Constructeur du bouton non appele");
}

void ComposantCadre::changeImage(string& nom)
{
	Surfaces* surfaces=Surfaces::getInstance();
	pair<int,int> ancienneTaille = surfaces->getSizeAnimationFirstImage(type.c_str());
	type=nom+".boutton";
	pair<int,int> nouvelleTaille = surfaces->getSizeAnimationFirstImage(type.c_str());

	if((ancienneTaille.first!=nouvelleTaille.first)||(ancienneTaille.second!=nouvelleTaille.second))
		animation=surfaces->getAnimation(type.c_str(),ancienneTaille.first,ancienneTaille.second);
	else animation=surfaces->getAnimation(type.c_str());
	imageCourante=(*animation).begin();
}

bool ComposantCadre::estClique(Uint16& x, Uint16& y)
{
	if((x>posX)&&(x<posX+(*imageCourante)->w)&&(y>posY)&&(y<posY+(*imageCourante)->h)) {
		return action();
	}  
	return false;
}						  


