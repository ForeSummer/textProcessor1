#ifndef CHARSTRINGLINK_H
#define CHARSTRINGLINK_H

#include "charString.h"

class charStringLink
{
public:
	charString* head;
	charString* tail;
	int length;
public:
	charStringLink();
	void initStringLink();
	void addString(charString &s);
	void deleteString(int index);
	int searchList(charString s);
};

#endif