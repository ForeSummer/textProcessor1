#include "stack.h"

Node::Node() {
	this->next = NULL;
}

Node::Node(charString myData) {
	this->data = myData;
	this->next = NULL;
}

Node::~Node() {
	this->next = NULL;
}

Stack::Stack() {
	this->stackLength = 0;
	this->base = NULL;
	this->top = NULL;
}

Stack::~Stack() {
	this->stackLength = 0;
	this->base = NULL;
	this->top = NULL;
}

void Stack::initStack() {
	this->stackLength = 0;
	this->base = NULL;
	this->top = NULL;
}

void Stack::push(Node* n) {
	if (this->base == NULL) {
		n->next = NULL;
		this->base = this->top = n;
		this->stackLength = 1;
	}
	else {
		n->next = this->top;
		this->top = n;
		this->stackLength++;
	}
	cout << n->data.toString()<<endl;
}

void Stack::pop() {
	if (this->isEmpty()) {
		return;
	}
	Node* p = this->top;
	cout << "/"<<this->top->data.toString()<<endl;
	this->top = this->top->next;
	this->stackLength --;
	delete p;
}

Node* Stack::getTop() {
	return this->top;
}

int Stack::isEmpty(){
	return stackLength == 0;
}