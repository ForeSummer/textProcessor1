#ifndef CHARSTRINGLINK_H
#define CHARSTRINGLINK_H

#include "charString.h"
#include "stack.h"


class charStringLink
{
public:
	Node* head;
	Node* tail;
	int length;
public:
	charStringLink();
	~charStringLink();
	void addStringNode(Node *n);
	void deleteStringNode(int index);
	int searchList(charString s);
	void outPutList(string outPath);
};


#endif