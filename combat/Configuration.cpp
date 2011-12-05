#include "Configuration.h"

Configuration* Configuration::_singleton=0;


/**
* \brief Constructeur de la classe Configuration.
*/
Configuration::Configuration()
{
	debug=Debug::getInstance();
	debug->print("Configuration constructor.");
#if 0
	if(chargement()==false) {
		MessageBoxA(NULL,"Le chargement de la configuration a echoue!","Erreur detecte",MB_ICONERROR|MB_OK);
	}
#endif
}

/**
* \brief Force l'existance unique d'un objet configuration.
* \details La première fois que la méthode est appelée, une instance de la classe est crée. Les fois suivantes, seul le pointeur vers la première instance est appelée
* 			et aucune autre instance n'est créée.
* \return Le pointeur vers l'unique instance de type Configuration.
*/
Configuration* Configuration::getInstance()
{
	if(_singleton==0) {
		_singleton = new Configuration();
		if(_singleton->chargement()==false) {
			MessageBox(NULL,"La configuration n'a pas pu être chargée!","FATAL ERROR",MB_OK|MB_ICONERROR);
			destruction();
		}
	}
	return _singleton;
}

/**
* \brief Libère la mémoire allouée à l'unique instance de la classe Configuration.
*/
Configuration* Configuration::destruction()
{
	delete _singleton;
	_singleton=0;
	return _singleton;
}


//template <typename T>
//T Configuration::get (const char* parametre)
//{
//	T retVal;
//
//	map<string, string>::iterator it = config.find(parametre);
//	if (it==config.end()) { // N'existe pas dans la config actuelle
//
//		// On signale l'erreur et on inscris en attendant la nouvelle valeur dans la configuration.
//		string msgErreur=string("Il manque la variable {")+string(parametre)+string("} dans la configuration. Entrez la valeur, puis ajoutez la ensuite dans le bon fichier.");
//        debug->print(msgErreur);
//#if 0
//		char valeur[100] = {0};
//		dialogueTr::InputBox(msgErreur.c_str(), parametre, valeur, sizeof(valeur),true);
//		//string value(buf);
//
//		config.insert(pair<string,string>(parametre,valeur));
//
//		return valeur;
//#endif
//	}
//	else { // Value found in config
//		stringstream ss;
//		ss << it->second;
//		ss >> retVal;
//	}
//	return retVal;
//}

/**
* \brief Récupère la valeur stockée dans le conteneur map.
* \param nomParametre Nom du paramètre à rechercher.
* \return La valeur du paramètre sous forme de chaine.
*/
string Configuration::getValeurParametre(const char* parametre)
{
	map<string, string>::iterator it = config.find(parametre);
	if (it==config.end()) { // N'existe pas dans la config actuelle

		// On signale l'erreur et on inscris en attendant la nouvelle valeur dans la configuration.
		string msgErreur=string("Il manque la variable {")+string(parametre)+string("} dans la configuration. Entrez la valeur, puis ajoutez la ensuite dans le bon fichier.");
        debug->print(msgErreur);
#ifdef WIN32
		char valeur[100] = {0};
		dialogueTr::InputBox(msgErreur.c_str(), parametre, valeur, sizeof(valeur),true);
		//string value(buf);

		config.insert(pair<string,string>(parametre,valeur));

		return valeur;
#endif
	}
	else { // Value found in config
		return it->second;
	}
	return "";
}

/**
* \brief Ordonne le chargement la configuration du jeu depuis plusieurs fichiers.
* \return true en cas de succès, false sinon.
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
* \param nomFichier nom du fichier contenant la configuration à charger.
* \return true en cas de succès, false sinon.
*/
bool Configuration::chargementFichier (string nomFichier)
{
	ifstream fichier(nomFichier.c_str());
	if (fichier.fail()) {
		debug->print("Cannot open file "+nomFichier);
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
	// lecture de la totalité du fichier
	ifstream fichierIn (fichier_config.c_str());
	if (fichierIn.fail()) {
		debug->print("Cannot open file " << fichier_config << endl;
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
		debug->print("Cannot open file " << fichier_config << " to write" << endl;
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
