#pragma once
#include "jsvar.h"

class JSBoolean : public JSVar
{
public:
	string toString(int depth = 0)const;
	bool value;
	JSBoolean(bool b) :value(b) {};
}jsTrue(true),jsFalse(false);

string JSBoolean::toString(int depth)const
{
	if (value)
		return { "TRUE" };
	else
		return { "FALSE" };
}