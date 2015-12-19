#ifndef DIC_H
#define DIC_H

#include "charString.h"
#include <iostream>
using namespace std;

//Á´±í½Úµã
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
	int fingInfo(int docID);
	void modifyInfo(int docID, int times);
};

#endif // !DIC_H
