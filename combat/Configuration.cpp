#include "Configuration.h"

Configuration* Configuration::_singleton=0;


/**
* \brief Constructeur de la classe Configuration.
*/
Configuration::Configuration()
{
	cout << "Configuration constructor." << endl; 
#if 0
	if(chargement()==false) {
		MessageBoxA(NULL,"Le chargement de la configuration a echoue!","Erreur detecte",MB_ICONERROR|MB_OK);
	}
#endif
}

/**
* \brief Force l'existance unique d'un objet configuration.
* \details La premi�re fois que la m�thode est appel�e, une instance de la classe est cr�e. Les fois suivantes, seul le pointeur vers la premi�re instance est appel�e
* 			et aucune autre instance n'est cr��e.
* \return Le pointeur vers l'unique instance de type Configuration.
*/
Configuration* Configuration::getInstance()
{
	if(_singleton==0) {
		_singleton = new Configuration();
		if(_singleton->chargement()==false) {
			MessageBox(NULL,"La configuration n'a pas pu �tre chargee!","FATAL ERROR",MB_OK|MB_ICONERROR);		
			destruction();
		}
	}
	return _singleton;
}

/**
* \brief Lib�re la m�moire allou�e � l'unique instance de la classe Configuration.
*/
Configuration* Configuration::destruction()
{
	delete _singleton;
	_singleton=0;
	return _singleton;
}

/**
* \brief R�cup�re la valeur stock�e dans le conteneur map.
* \param nomParametre Nom du param�tre � rechercher.
* \return La valeur du param�tre sous forme de chaine.
*/
string Configuration::getValeurParametre(const char* parametre)
{
	map<string, string>::iterator it = config.find(parametre);
	if (it==config.end()) { // N'existe pas dans la config actuelle
		
		// On signale l'erreur et on inscris en attendant la nouvelle valeur dans la configuration.
		string msgErreur=string("Il manque la variable {")+string(parametre)+string("} dans la configuration. Entrez la valeur, puis ajoutez la ensuite dans le bon fichier.");

		char valeur[100] = {0};
		dialogueTr::InputBox(msgErreur.c_str(), parametre, valeur, sizeof(valeur),true);
		//string value(buf);

		config.insert(pair<string,string>(parametre,valeur));
		return valeur;
	}
	else { // Value found in config
		return it->second;
	}
	return "";
}

/**
* \brief Ordonne le chargement la configuration du jeu depuis plusieurs fichiers.
* \return true en cas de succ�s, false sinon.
*/
bool Configuration::chargement()
{
	if(chargementFichier(fichierConfigApplication)==false)
		return false;
	
	if(chargementFichier(fichierConfigArme)==false)
		return false;

	if(chargementFichier(fichierConfigBalle)==false)
		return false;

	if(chargementFichier(fichierConfigImages)==false)
		return false;

	return true;
}

/**
* \brief Charge la configuration du jeu depuis un fichier.
* \param nomFichier nom du fichier contenant la configuration � charger.
* \return true en cas de succ�s, false sinon.
*/
bool Configuration::chargementFichier (string nomFichier)
{
	ifstream fichier(nomFichier.c_str());
	if (fichier.fail()) {
		cout << "Cannot open file " << nomFichier << endl;
		return false;
	}

	string ligne;
	stringstream ss;
	while (getline(fichier, ligne)) {
		ss.str("");
		ss.clear();
		ss << ligne;
		string clef, valeur;

		getline (ss, clef,';');
		getline (ss, valeur,';');
		config.insert(pair<string,string>(clef,valeur));
	}
	
	fichier.close();
	return true;
}

#if 0
int Configuration::deleteEntry (char* nameEntry, string fichier_config)
{
	map<string,string>::iterator it = config.find(string(nameEntry));
	if (it != config.end()) {
		config.erase(it);
	}
	// lecture de la totalit� du fichier
	ifstream fichierIn (fichier_config.c_str());
	if (fichierIn.fail()) {
		cout << "Cannot open file " << fichier_config << endl;
		return -1;
	}

	vector<string> fileContent;
	string line;
	while (getline(fichierIn, line)) {
		string::size_type pos = line.find(nameEntry);
		if (pos==string::npos)
			fileContent.push_back(line);
	}

	fichierIn.close();

	ofstream fichierOut (fichier_config.c_str());
	if (fichierOut.fail()) {
		cout << "Cannot open file " << fichier_config << " to write" << endl;
		return -1;
	}


	vector<string>::iterator itfileContent;
	for (itfileContent = fileContent.begin(); itfileContent != fileContent.end();itfileContent++) {
		fichierOut << *itfileContent << endl;
	}

	fichierOut.close();

	return 0;
}
#endif