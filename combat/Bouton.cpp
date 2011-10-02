#include "Bouton.h"

Bouton::Bouton()
{	
	this->application=0;
	cout << "Constructeur du bouton non appele" << endl;
}


// ------------------------------------------------------------------------------------
// ----------------------BOUTON ARME 1-------------------------------------------------
// ------------------------------------------------------------------------------------
BoutonArme1::BoutonArme1()
{	
	cout << "Constructeur BoutonArme1 appele!" << endl;
	this->application=Application::getInstance();
	this->configuration=Configuration::getInstance();
	init();
	load();
}

bool BoutonArme1::init()
{
	posX = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("boutonArme1.posX"))*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("boutonArme1.posY"))*application->resolution.second));
	return true;
}

bool BoutonArme1::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	//animation=application->surfaces->getAnimation("boutonArme1");
	pair<int, int> taille=surfaces->getSizeAnimationFirstImage("boutonArme1");
	int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation("boutonArme1", largeur, hauteur);
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonArme1::draw(SDL_Surface* screen)
{
	afficheEcran(posX, posY, screen, *imageCourante);
	return true;
}

// ------------------------------------------------------------------------------------
// ----------------------BOUTON ARME 2-------------------------------------------------
// ------------------------------------------------------------------------------------
BoutonArme2::BoutonArme2()
{	
	cout << "Constructeur BoutonArme2 appele!" << endl;
	this->application=Application::getInstance();
	this->configuration=Configuration::getInstance();
	init();
	load();
}

bool BoutonArme2::init()
{
	posX = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("boutonArme2.posX"))*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("boutonArme2.posY"))*application->resolution.second));
	return true;
}

bool BoutonArme2::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	pair<int, int> taille=surfaces->getSizeAnimationFirstImage("boutonNoWeapon");
	int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation("boutonNoWeapon", largeur, hauteur);
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonArme2::draw(SDL_Surface* screen)
{
	afficheEcran(posX, posY, screen, *imageCourante);
	return true;
}

// ------------------------------------------------------------------------------------
// ----------------------BOUTON ARME 3-------------------------------------------------
// ------------------------------------------------------------------------------------

BoutonArme3::BoutonArme3()
{	
	cout << "Constructeur BoutonArme3 appele!" << endl;
	this->application=Application::getInstance();
	this->configuration=Configuration::getInstance();
	init();
	load();
}

bool BoutonArme3::init()
{
	posX = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("boutonArme3.posX"))*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("boutonArme3.posY"))*application->resolution.second));
	return true;
}

bool BoutonArme3::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	animation=surfaces->getAnimation("boutonNoWeapon");
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonArme3::draw(SDL_Surface* screen)
{
	afficheEcran(posX, posY, screen, *imageCourante);
	return true;
}
// ------------------------------------------------------------------------------------
// ----------------------BOUTON ARME 4-------------------------------------------------
// ------------------------------------------------------------------------------------
BoutonArme4::BoutonArme4()
{	
	cout << "Constructeur BoutonArme4 appele!" << endl;
	this->application=Application::getInstance();
	this->configuration=Configuration::getInstance();
	init();
	load();
}

bool BoutonArme4::init()
{
	posX = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("boutonArme4.posX"))*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("boutonArme4.posY"))*application->resolution.second));
	return true;
}

bool BoutonArme4::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	animation=surfaces->getAnimation("boutonNoWeapon");
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonArme4::draw(SDL_Surface* screen)
{
	afficheEcran(posX, posY, screen, *imageCourante);
	return true;
}

// ------------------------------------------------------------------------------------
// ----------------------BOUTON AMELIORE ARME 1----------------------------------------
// ------------------------------------------------------------------------------------
BoutonAmelioreArme1::BoutonAmelioreArme1()
{	
	cout << "Constructeur BoutonAmelioreArme1 appele!" << endl;
	this->application=Application::getInstance();
	this->configuration=Configuration::getInstance();
	init();
	load();
}

bool BoutonAmelioreArme1::init()
{
	posX = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonAmelioreArme1.posX"))*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonAmelioreArme1.posY"))*application->resolution.second));
	return true;
}

bool BoutonAmelioreArme1::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	//animation=application->surfaces->getAnimation("BoutonAmelioreArme1");
	pair<int, int> taille=surfaces->getSizeAnimationFirstImage("BoutonAmelioreArme1");
	int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation("BoutonAmelioreArme1", largeur, hauteur);
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonAmelioreArme1::draw(SDL_Surface* screen)
{
	afficheEcran(posX, posY, screen, *imageCourante);
	return true;
}

// ------------------------------------------------------------------------------------
// ----------------------BOUTON AMELIORE ARME 2----------------------------------------
// ------------------------------------------------------------------------------------
BoutonAmelioreArme2::BoutonAmelioreArme2()
{	
	cout << "Constructeur BoutonAmelioreArme2 appele!" << endl;
	this->application=Application::getInstance();
	this->configuration=Configuration::getInstance();
	init();
	load();
}

bool BoutonAmelioreArme2::init()
{
	posX = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonAmelioreArme2.posX"))*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonAmelioreArme2.posY"))*application->resolution.second));
	return true;
}

bool BoutonAmelioreArme2::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	animation=surfaces->getAnimation("BoutonAmelioreArme1");
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonAmelioreArme2::draw(SDL_Surface* screen)
{
	afficheEcran(posX, posY, screen, *imageCourante);
	return true;
}

// ------------------------------------------------------------------------------------
// ----------------------BOUTON AMELIORE ARME 3----------------------------------------
// ------------------------------------------------------------------------------------
BoutonAmelioreArme3::BoutonAmelioreArme3()
{	
	cout << "Constructeur BoutonAmelioreArme3 appele!" << endl;
	this->application=Application::getInstance();
	this->configuration=Configuration::getInstance();
	init();
	load();
}

bool BoutonAmelioreArme3::init()
{
	posX = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonAmelioreArme3.posX"))*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonAmelioreArme3.posY"))*application->resolution.second));
	return true;
}

bool BoutonAmelioreArme3::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	animation=surfaces->getAnimation("BoutonAmelioreArme1");
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonAmelioreArme3::draw(SDL_Surface* screen)
{
	afficheEcran(posX, posY, screen, *imageCourante);
	return true;
}

// ------------------------------------------------------------------------------------
// ----------------------BOUTON AMELIORE ARME 4----------------------------------------
// ------------------------------------------------------------------------------------
BoutonAmelioreArme4::BoutonAmelioreArme4()
{	
	cout << "Constructeur BoutonAmelioreArme4 appele!" << endl;
	this->application=Application::getInstance();
	this->configuration=Configuration::getInstance();
	init();
	load();
}

bool BoutonAmelioreArme4::init()
{
	posX = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonAmelioreArme4.posX"))*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonAmelioreArme4.posY"))*application->resolution.second));
	return true;
}

bool BoutonAmelioreArme4::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	animation=surfaces->getAnimation("BoutonAmelioreArme1");
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonAmelioreArme4::draw(SDL_Surface* screen)
{
	afficheEcran(posX, posY, screen, *imageCourante);
	return true;
}

// ------------------------------------------------------------------------------------
// ----------------------BOUTON SUPPRIME ARME 1----------------------------------------
// ------------------------------------------------------------------------------------
BoutonSupprimeArme1::BoutonSupprimeArme1()
{	
	cout << "Constructeur BoutonSupprimeArme1 appele!" << endl;
	this->application=Application::getInstance();
	this->configuration=Configuration::getInstance();
	init();
	load();
}

bool BoutonSupprimeArme1::init()
{
	posX = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonSupprimeArme1.posX"))*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonSupprimeArme1.posY"))*application->resolution.second));
	return true;
}

bool BoutonSupprimeArme1::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	//animation=application->surfaces->getAnimation("BoutonSupprimeArme1");
	pair<int, int> taille=surfaces->getSizeAnimationFirstImage("BoutonSupprimeArme1");
	int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation("BoutonSupprimeArme1", largeur, hauteur);
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonSupprimeArme1::draw(SDL_Surface* screen)
{
	afficheEcran(posX, posY, screen, *imageCourante);
	return true;
}

// ------------------------------------------------------------------------------------
// ----------------------BOUTON SUPPRIME ARME 2----------------------------------------
// ------------------------------------------------------------------------------------
BoutonSupprimeArme2::BoutonSupprimeArme2()
{	
	cout << "Constructeur BoutonSupprimeArme2 appele!" << endl;
	this->application=Application::getInstance();
	this->configuration=Configuration::getInstance();
	init();
	load();
}

bool BoutonSupprimeArme2::init()
{
	posX = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonSupprimeArme2.posX"))*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonSupprimeArme2.posY"))*application->resolution.second));
	return true;
}

bool BoutonSupprimeArme2::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	animation=surfaces->getAnimation("BoutonSupprimeArme1");
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonSupprimeArme2::draw(SDL_Surface* screen)
{
	afficheEcran(posX, posY, screen, *imageCourante);
	return true;
}

// ------------------------------------------------------------------------------------
// ----------------------BOUTON SUPPRIME ARME 3----------------------------------------
// ------------------------------------------------------------------------------------
BoutonSupprimeArme3::BoutonSupprimeArme3()
{	
	cout << "Constructeur BoutonSupprimeArme3 appele!" << endl;
	this->application=Application::getInstance();
	this->configuration=Configuration::getInstance();
	init();
	load();
}

bool BoutonSupprimeArme3::init()
{
	posX = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonSupprimeArme3.posX"))*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonSupprimeArme3.posY"))*application->resolution.second));
	return true;
}

bool BoutonSupprimeArme3::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	animation=surfaces->getAnimation("BoutonSupprimeArme1");
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonSupprimeArme3::draw(SDL_Surface* screen)
{
	afficheEcran(posX, posY, screen, *imageCourante);
	return true;
}

// ------------------------------------------------------------------------------------
// ----------------------BOUTON SUPPRIME ARME 4----------------------------------------
// ------------------------------------------------------------------------------------
BoutonSupprimeArme4::BoutonSupprimeArme4()
{	
	cout << "Constructeur BoutonSupprimeArme4 appele!" << endl;
	this->application=Application::getInstance();
	this->configuration=Configuration::getInstance();
	init();
	load();
}

bool BoutonSupprimeArme4::init()
{
	posX = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonSupprimeArme4.posX"))*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonSupprimeArme4.posY"))*application->resolution.second));
	return true;
}

bool BoutonSupprimeArme4::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	animation=surfaces->getAnimation("BoutonSupprimeArme1");
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonSupprimeArme4::draw(SDL_Surface* screen)
{
	afficheEcran(posX, posY, screen, *imageCourante);
	return true;
}
// ------------------------------------------------------------------------------------
// ----------------------BOUTON GRADE--------------------------------------------------
// ------------------------------------------------------------------------------------
BoutonGrade::BoutonGrade()
{	
	cout << "Constructeur BoutonGrade appele!" << endl;
	this->application=Application::getInstance();
	this->configuration=Configuration::getInstance();
	init();
	load();
}

bool BoutonGrade::init()
{
	posX = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonGrade.posX"))*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonGrade.posY"))*application->resolution.second));
	return true;
}

bool BoutonGrade::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	//animation=surfaces->getAnimation("BoutonGrade");
	pair<int, int> taille=surfaces->getSizeAnimationFirstImage("BoutonGrade");
	int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation("BoutonGrade", largeur, hauteur);
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonGrade::draw(SDL_Surface* screen)
{
	afficheEcran(posX, posY, screen, *imageCourante);
	return true;
}

// ------------------------------------------------------------------------------------
// ----------------------BOUTON VIE----------------------------------------------------
// ------------------------------------------------------------------------------------
BoutonVie::BoutonVie()
{	
	cout << "Constructeur BoutonVie appele!" << endl;
	this->application=Application::getInstance();
	this->configuration=Configuration::getInstance();
	init();
	load();
}

bool BoutonVie::init()
{
	posX = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonVie.posX"))*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonVie.posY"))*application->resolution.second));
	return true;
}

bool BoutonVie::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	//animation=surfaces->getAnimation("BoutonVie");
	pair<int, int> taille=surfaces->getSizeAnimationFirstImage("BoutonVie");
	int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation("BoutonVie", largeur, hauteur);
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonVie::draw(SDL_Surface* screen)
{
	afficheEcran(posX, posY, screen, *imageCourante);
	return true;
}

// ------------------------------------------------------------------------------------
// ----------------------BOUTON DEFENSE------------------------------------------------
// ------------------------------------------------------------------------------------
BoutonDefense::BoutonDefense()
{	
	cout << "Constructeur BoutonDefense appele!" << endl;
	this->application=Application::getInstance();
	this->configuration=Configuration::getInstance();
	init();
	load();
}

bool BoutonDefense::init()
{
	posX = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonDefense.posX"))*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonDefense.posY"))*application->resolution.second));
	return true;
}

bool BoutonDefense::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	//animation=surfaces->getAnimation("BoutonDefense");
	pair<int, int> taille=surfaces->getSizeAnimationFirstImage("BoutonDefense");
	int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation("BoutonDefense", largeur, hauteur);
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonDefense::draw(SDL_Surface* screen)
{
	afficheEcran(posX, posY, screen, *imageCourante);
	return true;
}

// ------------------------------------------------------------------------------------
// ----------------------BOUTON SUPPORT------------------------------------------------
// ------------------------------------------------------------------------------------
BoutonSupport::BoutonSupport()
{	
	cout << "Constructeur BoutonSupport appele!" << endl;
	this->application=Application::getInstance();
	this->configuration=Configuration::getInstance();
	init();
	load();
}

bool BoutonSupport::init()
{
	posX = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonSupport.posX"))*application->resolution.first));
	posY = static_cast<int>(ceil(stringToFloat(configuration->getValeurParametre("BoutonSupport.posY"))*application->resolution.second));
	return true;
}

bool BoutonSupport::load()
{
	Surfaces* surfaces=Surfaces::getInstance();
	//animation=application->surfaces->getAnimation("BoutonSupport");
	pair<int, int> taille=surfaces->getSizeAnimationFirstImage("BoutonSupport");
	int largeur = static_cast<int>(ceil(taille.first*application->resolution.first));
	int hauteur = static_cast<int>(ceil(taille.second*application->resolution.second));
	animation=surfaces->getAnimation("BoutonSupport", largeur, hauteur);
	imageCourante=(*animation).begin();
	return true;
}

bool BoutonSupport::draw(SDL_Surface* screen)
{
	afficheEcran(posX, posY, screen, *imageCourante);
	return true;
}
