#pragma once

#include <string>

#include "jsvar.h"

using std::string;

class JSString :public JSVar
{
private:
	string value;
public:
	JSString(const string& str) :value(str) {};
	JSString() {};
	string toString(int depth = 0)const;
};
string JSString::toString(int depth)const
{
	return value;
}
