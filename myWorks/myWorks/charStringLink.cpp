#include "charStringLink.h"

charStringNode::charStringNode() {
	this->next = NULL;
}

charStringNode::charStringNode(charString* s) {
	this->data = s; 
	this->next = NULL;
}

charStringNode::~charStringNode() {
	delete this->data;
}

charStringLink::charStringLink() {
	this->head = this->tail = NULL;
	this->length = 0;
}


void charStringLink::addStringNode(charString* s) {
	 charStringNode node(s);
	 if (this->head == NULL) {
		 this->head = this->tail = &node;
		 this->length = 1;
	 }
	 else {
		 this->tail->next = &node;
		 this->tail = &node;
		 this->length ++;
	 }
}

void charStringLink::deleteStringNode(int index) {
	if (index >= this->length) {
		return;
	}
	if (index == 0)	{
		if (this->length == 0) {
			delete this->head;
			this->head = this->tail = NULL;
		}
		charStringNode *p;
		p = this->head;
		this->head = this->head->next;
		delete p;
		this->length --;
		return;
	}
	else if(index == this->length - 1) {
		charStringNode *p;
		p = this->head;
		for (int i = 0; i < index; i++)	{
			p = p->next;
		}
		p->next = NULL;
		delete this->tail;
		this->tail = p;
		this->length --;
		return;
	}
	else {
		charStringNode *p, *q;
		p = q = this->head;
		for (int i = 0; i < index; i++)	{
			p = q = p->next;
		}
		p = p->next;
		q->next = p->next;
		delete p;
		this->length --;
		return;
	}
}