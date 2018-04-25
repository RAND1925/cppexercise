#pragma once
#pragma once

#include "jsvar.h"

class JSNull : public JSVar
{
public:
	string toString(int depth = 0)const;
}jsNull;

string JSNull::toString(int depth)const
{
	return { "NULL" };
}