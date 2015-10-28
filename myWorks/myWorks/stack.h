#ifndef STACK_H
#define STACK_H

#include <string>
#include <iostream>
using namespace std;
#define STACK_SIZE 100


class Node
{
public:
	string data;
	Node* next;
	Node();
	Node(string myData, Node* pointer = NULL);
};

class Stack
{
private:
	Node *base;
	Node *top;
	int stackSize;
	int stackLength;
public:
	Stack();
	void initStack();
	void pop();
	void push(string myData);
	string getTop();
	int isEmpty();
};

#endif