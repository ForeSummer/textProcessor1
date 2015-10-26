#ifndef CHARSTRING_H
#define CHARSTRING_H

#include <iostream>
#include <string>
using namespace std;

class charString
{
public:
	char* line;
	charString();
	charString(string s);
	charString(char* c);
	char indexOf(int index);
	charString subString(string s, int index, int length);
	charString subString(charString s, int index, int length);
	charString concat(string s1, string s2);
	charString concat(charString s1, charString s2);
};

class stringList
{
public:
	charString* list;
};

#endif