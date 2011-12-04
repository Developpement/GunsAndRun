#include "Debug.h"

Debug* Debug::_singleton = 0;


Debug* Debug::getInstance()
{
	if(_singleton==0)
		_singleton=new Debug();

	return _singleton;
}


Debug* Debug::destruct()
{
	if(_singleton)
		delete _singleton;
	_singleton=0;
	return _singleton;
}


void Debug::print(string& Msg)
{
	cout << Msg << endl;
	ofstream file (logFileName, ios::app);
	if(file.fail()) {
		cout << "Cannot open file "<<logFileName<<endl;
		return;
	}

	time_t theTime;
	struct tm timeInfo;

	time(&theTime);
	localtime_s(&timeInfo,&theTime);	
	file <<logNb<<" - "<<timeInfo.tm_hour<<":"<<timeInfo.tm_min<<":"<<timeInfo.tm_sec<<" - "<<Msg<<endl;
	file.close();

	logNb++;
}

void Debug::print(char* str)
{
	string msg(str);
	print(msg);
}


Debug::Debug()
{
	ofstream file(logFileName);
	file.close();
	logNb=0;
}
