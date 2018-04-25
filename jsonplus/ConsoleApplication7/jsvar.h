#pragma once

#include <string>
#include <iostream>
using std::string;

class JSVar
{
public:
	virtual void readin(char);
	void display();
	virtual string toString(int depth = 0)const = 0;
	virtual ~JSVar();
};
void JSVar::readin(char a) {};

void JSVar::display()
{
	std::cout << toString();
};

JSVar::~JSVar() {};

