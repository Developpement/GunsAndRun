#pragma once


#include "Gestionnaire.h"
#include "ConfigurationJeu.h"
#include "Debug.h"
class Gestionnaire;

enum TypeBouttons {
	BOUTTONS_SELECTION_ARME=0,
	BOUTTONS_MODIFICATIONS_ARME,
	BOUTTONS_APTITUDE_PERSONNAGE,
	BOUTTONS_MENU
};


class Bouton
{
public:
	TypeBouttons typeBouttons;

	int posX,posY; // position de l'image sur l'�cran
	Gestionnaire* application;
	ConfigurationJeu* configuration;
	Debug* debug;

	vector<SDL_Surface*>* animation;
	vector<SDL_Surface*>::iterator imageCourante;

	string type;

	Bouton();
	virtual bool init()=0;
	virtual bool load()=0;
	virtual bool draw(SDL_Surface* screen)=0;
	virtual void changeImage(string& nom);
	virtual bool action()=0;
	bool estClique(Uint16& x, Uint16& y);
};


/*
 * BOUTON ARME 1
 */
class BoutonArme1 : public Bouton
{
public:
	BoutonArme1();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};

/*
 * BOUTON ARME 1
 */
class BoutonArme2 : public Bouton
{
public:
	BoutonArme2();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};

/*
 * BOUTON ARME 1
 */
class BoutonArme3 : public Bouton
{
public:
	BoutonArme3();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};

/*
 * BOUTON ARME 1
 */
class BoutonArme4 : public Bouton
{
public:
	BoutonArme4();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};

/*
 * BOUTON ARMELIORE ARME 1
 */
class BoutonAmelioreArme1 : public Bouton
{
public:
	BoutonAmelioreArme1();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};


/*
 * BOUTON ARMELIORE ARME 2
 */
class BoutonAmelioreArme2 : public Bouton
{
public:
	BoutonAmelioreArme2();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};

/*
 * BOUTON ARMELIORE ARME 3
 */
class BoutonAmelioreArme3 : public Bouton
{
public:
	BoutonAmelioreArme3();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};

/*
 * BOUTON ARMELIORE ARME 4
 */
class BoutonAmelioreArme4 : public Bouton
{
public:
	BoutonAmelioreArme4();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};


/*
 * BOUTON SUPPRIME ARME 1
 */
class BoutonSupprimeArme1 : public Bouton
{
public:
	BoutonSupprimeArme1();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};

/*
 * BOUTON SUPPRIME ARME 2
 */
class BoutonSupprimeArme2 : public Bouton
{
public:
	BoutonSupprimeArme2();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};

/*
 * BOUTON SUPPRIME ARME 3
 */
class BoutonSupprimeArme3 : public Bouton
{
public:
	BoutonSupprimeArme3();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};

/*
 * BOUTON SUPPRIME ARME 4
 */
class BoutonSupprimeArme4 : public Bouton
{
public:
	BoutonSupprimeArme4();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};

/*
 * BOUTON GRADE
 */
class BoutonGrade : public Bouton
{
public:
	BoutonGrade();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};

/*
 * BOUTON VIE
 */
class BoutonVie : public Bouton
{
public:
	BoutonVie();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};

/*
 * BOUTON DEFENSE
 */
class BoutonDefense : public Bouton
{
public:
	BoutonDefense();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};

/*
 * BOUTON SUPPORT
 */
class BoutonSupport : public Bouton
{
public:
	BoutonSupport();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};

/*
 * BOUTON MENU
 */
class BoutonMenu : public Bouton
{
public:
	BoutonMenu();

	virtual bool init();
	virtual bool load();
	virtual bool draw(SDL_Surface* screen);
	virtual bool action();
};
