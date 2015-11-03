#include "charStringLink.h"
#include <fstream>


charStringLink::charStringLink() {
	this->head = this->tail = NULL;
	this->length = 0;
}

charStringLink::~charStringLink() {
	Node *p, *q;
	p = q = this->head;
	while (p != NULL) {
		q = p;
		p = p->next;
		delete q;
	}
}

void charStringLink::addStringNode(Node *node) {
	 if (this->head == NULL) {
		 this->head = this->tail = node;
		 this->length = 1;
	 }
	 else {
		 this->tail->next = node;
		 this->tail = node;
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
		Node *p;
		p = this->head;
		this->head = this->head->next;
		delete p;
		this->length --;
		return;
	}
	else if(index == this->length - 1) {
		Node *p;
		p = this->head;
		for (int i = 0; i < index - 1; i++)	{
			p = p->next;
		}
		p->next = NULL;
		delete this->tail;
		this->tail = p;
		this->length --;
		return;
	}
	else {
		Node *p, *q;
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

void charStringLink::outPutList(string outPath) {
	ofstream outFs(outPath, ios::out);
	if (this->head == NULL) {
		outFs.close();
		return;
	}
	Node *p;
	p = head;
	while (p != NULL) {
		outFs << p->data.toString() << endl;
		p = p->next;
	}
	outFs.close();
	return;
}