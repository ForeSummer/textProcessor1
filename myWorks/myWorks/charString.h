#ifndef CHARSTRING_H
#define CHARSTRING_H

#include <iostream>
#include <string>
using namespace std;

class charString
{
public:
	char* line;
	int length;
public:
	charString();
	charString(string s);
	charString(char* c);
	charString(charString& s);
	~charString();
	int indexOf(char ch);
	string toString();
	void deleteChar(int index);
	charString subString(int index, int length);
	charString concat(charString s);
	bool operator == (charString& s);
	bool operator < (charString& s);
	bool operator > (charString& s);
	charString& operator = (const charString& s);
};



#endif