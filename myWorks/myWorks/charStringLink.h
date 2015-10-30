#ifndef CHARSTRINGLINK_H
#define CHARSTRINGLINK_H

#include "charString.h"

class charStringNode
{
public:
	charString* data;
	charStringNode* next;
public:
	charStringNode();
	charStringNode(charString* s);
	~charStringNode();
};

class charStringLink
{
public:
	charStringNode* head;
	charStringNode* tail;
	int length;
public:
	charStringLink();
	void addStringNode(charString* s);
	void deleteStringNode(int index);
	int searchList(charString s);
};

#endif