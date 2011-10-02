#pragma once
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

template <typename T>
inline string toString (T& value)
{
	stringstream ss;
	ss << value;
	return ss.str();
}


inline int stringToInt (string& value)
{
	int retVal;
	stringstream ss;
	ss << value;
	ss >> retVal;
	return retVal;
}

inline float stringToFloat (string& value)
{
	float retVal;
	stringstream ss;
	ss << value;
	ss >> retVal;
	return retVal;
}

inline unsigned int stringToUInt (string& value)
{
	unsigned int retVal;
	stringstream ss;
	ss << value;
	ss >> retVal;
	return retVal;
}


/**
* \brief		Fast convertion from a std::wstring to a std::string used for ASCII
*				characters only.
* \param		wstr	  Thr wide string to convert.
* \return	A std::string with all caracters that were in the wstring input
*				parameter.
*/
inline string wstringToString(const wstring& wstr) 
{
	string str(wstr.begin(),wstr.end());
	return str;
}
/**
* \brief		Fast convertion from a std::string to a std::wstring used for ASCII
*				characters only.
* \param		str	  Thr string to convert.
* \return	A std::wstring with all caracters that were in the string input
*				parameter.
*/
inline wstring stringToWstring(const string& str) 
{
	wstring wstr(str.length(),L' ');
	copy(str.begin(),str.end(),wstr.begin());
	return wstr;
}