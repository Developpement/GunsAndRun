#include "ConfigurationJeu.h"

ConfigurationJeu* ConfigurationJeu::_singleton=0;


/**
* \brief Constructeur de la classe ConfigurationJeu.
*/
ConfigurationJeu::ConfigurationJeu()
{
	debug=Debug::getInstance();
	debug->print("ConfigurationJeu constructor.");
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
* \return Le pointeur vers l'unique instance de type ConfigurationJeu.
*/
ConfigurationJeu* ConfigurationJeu::getInstance()
{
	if(_singleton==0) {
		_singleton = new ConfigurationJeu();
		if(_singleton->chargement()==false) {
			MessageBox(NULL,"La configuration n'a pas pu �tre charg�e!","FATAL ERROR",MB_OK|MB_ICONERROR);
			destruction();
		}
	}
	return _singleton;
}

/**
* \brief Lib�re la m�moire allou�e � l'unique instance de la classe ConfigurationJeu.
*/
ConfigurationJeu* ConfigurationJeu::destruction()
{
	delete _singleton;
	_singleton=0;
	return _singleton;
}


//template <typename T>
//T ConfigurationJeu::get (const char* parametre)
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
* \brief R�cup�re la valeur stock�e dans le conteneur map.
* \param nomParametre Nom du param�tre � rechercher.
* \return La valeur du param�tre sous forme de chaine.
*/
string ConfigurationJeu::getValeurParametre(const char* parametre, bool rensigneParametre)
{
	map<string, string>::iterator it = config.find(parametre);
	if (it==config.end()) { // N'existe pas dans la config actuelle

		if(rensigneParametre) {
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
bool ConfigurationJeu::chargement()
{
	if(chargementFichier(fichierConfigApplication)==false)
		return false;

	if(chargementFichier(fichierConfigArme)==false)
		return false;

	if(chargementFichier(fichierConfigBalle)==false)
		return false;

	if(chargementFichier(fichierConfigImages)==false)
		return false;

	string nomMap=getValeurParametre("map");
	if(chargementFichier(nomMap+".txt")==false)
		return false;

	return true;
}

/**
* \brief Charge la configuration du jeu depuis un fichier.
* \param nomFichier nom du fichier contenant la configuration � charger.
* \return true en cas de succ�s, false sinon.
*/
bool ConfigurationJeu::chargementFichier (string nomFichier)
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
		map<string,string>::iterator it=config.find(clef);
		if(it==config.end())
			config.insert(pair<string,string>(clef,valeur));
		else it->second=valeur;
	}

	fichier.close();
	return true;
}

#if 0
int ConfigurationJeu::deleteEntry (char* nameEntry, string fichier_config)
{
	map<string,string>::iterator it = config.find(string(nameEntry));
	if (it != config.end()) {
		config.erase(it);
	}
	// lecture de la totalit� du fichier
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
