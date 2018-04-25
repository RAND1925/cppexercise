#pragma once

#include "jsvar.h"

class JSNull: public JSVar 
{
public:
	string toString();
}null;

string JSNull::toString()
{
	return {"NULL"};
}