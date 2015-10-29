#include "charStringLink.h"

charStringLink::charStringLink() {

}

void charStringLink::initStringLink() {
	this->head = this->tail = NULL;
	this->length = 0;
}

void charStringLink::addString(charString &s) {
	if (head == NULL) {
		head = tail = &s;
		length = 1;
	}
	else
	{
		tail = &s;
		length ++;
	}
}

void charStringLink::deleteString(int index) {

}