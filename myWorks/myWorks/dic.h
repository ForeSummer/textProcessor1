#ifndef DIC_H
#define DIC_H

#include <string>
#include <iostream>
#include "BTree.h"
using namespace std;

class word
{
public:
	string term;
	int termID;
	int DF;
	int occur;
	docNode *docInfo;
	word();
	void addNewInfo(int docID);
};

class docNode
{
public:
	int docID;
	int times;
	docNode *next;
	docNode();
};

class invertedFile
{
public:
	BTree myFile;
	void buildFile(string path);
	void insertFile(string filePath);
	void saveFile(string filePath);
	invertedFile(string filePath);
};
#endif // !DIC_H
