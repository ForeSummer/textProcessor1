#ifndef DIC_H
#define DIC_H

#include "charString.h"
#include <iostream>
using namespace std;

class docNode
{
public:
	int docID;
	int times;
	docNode *next;
	docNode();
};

class word
{
public:
	charString term;
	int termID;
	int DF;
	int occur;
	docNode* docInfo;
	word();
	~word();
	void addNewInfo(int docID);
};

#endif // !DIC_H
