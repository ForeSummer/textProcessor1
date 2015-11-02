#include "charString.h"
#include <iostream>
using namespace std;

charString::charString() {
	this->length = 0;
	this->line = NULL;
}

charString::charString(string s) {
	this->length = s.length();
	this->line = new char[this->length + 1];
	char* temp = this->line;
	for (int i = 0; i < this->length; i++) {
		*temp = s[i];
		temp ++;
	}
	*temp = '\0';
}

charString::charString(char* s) {
	this->line = s;
	int length = strlen(s);
}

charString::charString(charString& s){
	this->length = s.length;
	this->line = new char[this->length + 1];
	char* temp = this->line;
	for (int i = 0; i < length; i++) {
		*temp = s.line[i];
		temp ++;
	}
	*temp = '\0';
}

int charString::indexOf(char ch) {
	int index = 0;
	while (index < this->length) {
		if (this->line[index] == ch) {
			break;
		}
		index ++;
	}
	if (index == this->length) {
		return -1;
	}
	return index;
}

string charString::toString() {
	string s = "";
	if (this->length == 0) {
		return s;
	}
	for (int i = 0; i < this->length; i++)
	{
		s = s + this->line[i];
	}
	return s;
}

charString charString::subString(int index, int length) {
	if (length > this->length - index) {
		length = this->length - index;
	}
	charString s;
	s.length = length;
	s.line = new char[length + 1];
	char* temp = s.line;
	for (int i = index; i < index + length; i ++) {
		*temp = this->line[i];
		temp ++;
	}
	*temp = '\0';
	return s;
}

charString charString::concat(charString s) {
	charString result;
	result.length = this->length + s.length;
	result.line = new char[result.length + 1];
	char* temp = result.line;
	for (int i = 0; i < this->length; i ++) {
		*temp = this->line[i];
		temp ++;
	}
	for (int i = 0; i < s.length; i++)	{
		*temp = s.line[i];
		temp ++;
	}
	*temp = '\0';
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
	this->line = new char[this->length + 1];
	char* temp = this->line;
	for (int i = 0; i < this->length + 1; i++) {
		*temp = s.line[i];
		temp ++;
	}
	return *this;
}