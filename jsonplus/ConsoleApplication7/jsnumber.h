#pragma once
#pragma once

#include <string>
#include <sstream>
#include "jsvar.h"

using std::string;
using std::stringstream;

class JSNumber :public JSVar
{
private:
	long double value = 0;
public:
	JSNumber(const string& str);
	JSNumber() {};
	string toString(int depth = 0)const;
};

JSNumber::JSNumber(const string& str)
{
	stringstream ssStr(str);
	ssStr >> value;
};
string JSNumber::toString(int depth)const
{
	string tmp;
	stringstream ssTmp(tmp);
	ssTmp << value;
	ssTmp >> tmp;
	return  tmp;
}


