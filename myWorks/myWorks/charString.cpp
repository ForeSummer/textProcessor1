#include "charString.h"

charString::charString() {
	this->length = 0;
	this->line = NULL;
}

charString::charString(string s) {
	strcpy(this->line, s.c_str);
	this->length = strlen(s.c_str);
}

charString::charString(char* s) {
	this->line = s;
	int length = strlen(s);
}

charString::charString(charString& s){
	strcpy(this->line, s.line);
	this->length = s.length;
}

char charString::indexOf(int index) {
	if (index >= this->length)
		return -1;
	return this->line[index];
}

int charString::getLength() {
	return this->length;
}

void charString::subString(int index, int length) {
	for (int i = index; i < index + length; i ++) {
		this->line[i - index] = this->line[i];
	}
	this->line[length] = this->line[index + length];
	this->length = length;
}