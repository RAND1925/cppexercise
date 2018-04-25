#pragma once

#include <map>
#include <string>

#include "JSVar.h"
#include "JSString.h"

using std::map;
using std::string;
class JSObject :public JSVar
{
private:
	map<string, JSVar*> members;
public:
	typedef std::pair<string, JSVar*> JSPair;
	string toString(int depth = 0)const;
	void push(JSPair);
	~JSObject();
	JSVar* operator[] (string s) { return members[s]; };
};

JSObject::~JSObject()
{
	for (auto iter = members.begin(); iter != members.end(); ++iter)
	{
		delete &(*iter);
	}
}

string JSObject::toString(int depth)const
{
	string res("{\n");
	for (auto iter = members.begin(); iter != members.end(); ++iter)
	{
		for (int i = 0; i < depth + 1; ++i)
		{
			res += '\t';
		}
		res += iter->first;
		res += ":";
		res += iter->second->toString(depth + 1);
		res += "\n";
	}
	for (int i = 0; i < depth ; ++i)
	{
		res += '\t';
	}
	res += "}";
	return res;
}
void JSObject::push(JSPair p)
{
	members.insert(p);
}
