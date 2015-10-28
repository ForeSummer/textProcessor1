#include "stack.h"

Node::Node() {
	next = NULL;
}
Node::Node(string myData, Node* pointer = NULL) {
	data = myData;
	next = pointer;
}

Stack::Stack() {
	this->stackSize = 0;
	this->base = NULL;
	this->top = NULL;
}

void Stack::initStack() {
	this->base = new Node[STACK_SIZE];
	if (!this->base)
		exit(OVERFLOW);
	this->top = this->base;
	stackLength = 0;
	this->stackSize = STACK_SIZE;
}

void Stack::push(string myData) {
	if (this->top - this->base >= this->stackSize)
		return;
	*this->top ++ = Node(myData);
}

void Stack::pop() {
	if (this->top = this->base)
		return;
	*this->top --;
}

string Stack::getTop() {
	return this->top->data;
}

int Stack::isEmpty(){
	return stackLength == 0;
}