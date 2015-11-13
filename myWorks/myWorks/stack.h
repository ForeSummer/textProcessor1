#ifndef STACK_H
#define STACK_H

#include "charString.h"



class Node
{
public:
	charString data;
	Node* next;
public:
	Node();
	~Node();
	Node(charString myData);
};

class Stack
{
public:
	Node *base;
	Node *top;
	int stackLength;
public:
	Stack();
	~Stack();
	void initStack();
	void pop();
	void push(Node* n);
	Node* getTop();
	int isEmpty();
};

#endif