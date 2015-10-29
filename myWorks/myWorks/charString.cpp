#include "charString.h"

charString::charString() {
	this->length = 0;
	this->line = NULL;
}

charString::charString(string s) {
	this->length = strlen(s.c_str);
	this->line = new char[this->length + 1];
	for (int i = 0; i < length; i++) {
		this->line[i] = s[i];
	}
	this->line[this->length] = '\0';
}

charString::charString(char* s) {
	this->line = s;
	int length = strlen(s);
}

charString::charString(charString& s){
	this->length = s.length;
	this->line = new char[this->length + 1];
	for (int i = 0; i < length; i++) {
		this->line[i] = s.line[i];
	}
	this->line[this->length] = '\0';
}

char charString::indexOf(int index) {
	if (index >= this->length)
		return -1;
	return this->line[index];
}

int charString::getLength() {
	return this->length;
}

charString charString::subString(int index, int length) {
	if (length > this->length - index) {
		length = this->length - index;
	}
	charString s;
	s.length = length;
	s.line = new char[length + 1];
	for (int i = index; i < index + length; i ++) {
		s.line[i - index] = this->line[i];
	}
	s.line[length] = '\0';
	return s;
}

charString charString::concat(charString s) {
	charString result;
	result.length = this->length + s.length;
	result.line = new char[result.length + 1];
	for (int i = 0; i < this->length; i ++) {
		result.line[i] = this->line[i];
	}
	for (int i = this->length; i < this->length + s.length; i++)	{
		result.line[i] = s.line[i - length];
	}
	result.line[result.length] = '\0';
	return result;
}

bool charString::operator== (charString& s) {
	if (s.length != this->length) {
		return false;
	}
	for (int i = 0; i < this->length; i++) {
		if (this->line[i] != s.line[i]) {
			return false;
		}
	}
	return true;
}
charString& charString::operator= (const charString& s) {
	this->length = s.length;
	for (int i = 0; i <= this->length; i++) {
		this->line[i] = s.line[i];
	}
	return *this;
}