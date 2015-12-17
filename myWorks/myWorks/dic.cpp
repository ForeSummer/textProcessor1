#include "dic.h"
#include <fstream>
#include <io.h>
#include <vector>


word::word() {
	this->DF = 0;
	this->termID = -1;
	this->occur = 0;
}

word::~word() {
	for (int i = 0; i < this->docInfo.size(); i++) {
		delete this->docInfo[i];
	}
}

docNode::docNode() {
	this->docID = -1;
	this->times = 0;
}


void word::addNewInfo(int docID) {
	docNode *p;
	for (int i = 0; i < this->docInfo.size(); i ++) {
		if (this->docInfo[i]->docID == docID) {
			this->docInfo[i]->times ++;
			return;
		}
	}
	p = new docNode();
	p->docID = docID;
	p->times ++;
	this->DF ++;
	return;
}

