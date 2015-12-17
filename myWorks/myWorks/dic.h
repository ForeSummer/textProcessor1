#ifndef DIC_H
#define DIC_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class docNode
{
public:
	int docID;
	int times;
	docNode();
};

class word
{
public:
	string term;
	int termID;
	int DF;
	int occur;
	vector<docNode*> docInfo;
	word();
	~word();
	void addNewInfo(int docID);
};

#endif // !DIC_H
