#include "dic.h"
#include <fstream>
#include <io.h>
#include <vector>


word::word() {
	this->DF = 0;
	this->termID = -1;
	this->occur = 0;
	this->docInfo = NULL;
}

word::~word() {
	docNode *p, *q;
	p = q = this->docInfo;
	while (p != NULL) {
		q = p;
		p = p->next;
		delete q;
	}
}

docNode::docNode() {
	this->docID = -1;
	this->times = 0;
	this->next = NULL;
}


void word::addNewInfo(int docID) {
	docNode *p, *q;
	p = this->docInfo;
	if (p == NULL) {
		this->docInfo = new docNode();
		this->docInfo->docID = docID;
		this->docInfo->times ++;
		this->DF ++;
		return;
	}
	while (p->next != NULL) {
		if (p->docID == docID) {
			p->times ++;
			return;
		}
		p = p->next;
	}
	if (p->docID == docID) {
		p->times ++;
		return;
	}
	q = new docNode();
	q->docID = docID;
	q->times ++;
	p->next = q;
	this->DF ++;
	return;
}

