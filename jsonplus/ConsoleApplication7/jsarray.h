#pragma once

#include <string>
#include <vector>
#include <iterator>

#include "jsvar.h"

using std::vector;
using std::string;

class JSArray :public JSVar
{
private:
	vector<JSVar*> elements;
public:
	JSArray() {};
	string toString(int depth = 0)const;
	void push_front(JSVar*);
	~JSArray();
	JSVar* operator [](int n) { return elements[n];}
};

JSArray::~JSArray()
{
	for (auto iter = elements.begin(); iter != elements.end(); ++iter)
	{
		delete &(*iter);
	}
}

string JSArray::toString(int depth)const
{
	string res("[\n");
	int i = 0;
	for (auto iter = elements.begin(); iter != elements.end(); ++iter, ++i)
	{
		for (int i = 0 ; i < depth + 1; ++i)
		{
			res += '\t';
		}
		res += (*iter)->toString(depth + 1);
		res += "\n";
	}
	for (int i = 0; i < depth ; ++i)
	{
		res += '\t';
	}
	res += "]";
	return res;
}

void JSArray::push_front(JSVar* p)
{
	elements.insert(elements.begin(),p);
}
