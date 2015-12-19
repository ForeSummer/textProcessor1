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

//加入信息同时更新链表并排序
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
			int tempID, tempTimes;
			p = this->docInfo;
			while (p->next != NULL) {
				q = p->next;
				if (q->times >p->times) {
					tempTimes = q->times;
					tempID = q->docID;
					q->times = p->times;
					q->docID = p->docID;
					p->times = tempTimes;
					p->docID = tempID;
				}
				p = p->next;
			}
			return;
		}
		p = p->next;
	}
	if (p->docID == docID) {
		p->times ++;
		int tempID, tempTimes;
		p = this->docInfo;
		while (p->next != NULL) {
			q = p->next;
			if (q->times >p->times) {
				tempTimes = q->times;
				tempID = q->docID;
				q->times = p->times;
				q->docID = p->docID;
				p->times = tempTimes;
				p->docID = tempID;
			}
			p = p->next;
		}
		return;
	}
	q = new docNode();
	q->docID = docID;
	q->times ++;
	p->next = q;
	this->DF ++;

	//rank
	
	return;
}

int word::fingInfo(int docID) {
	docNode *p;
	p = this->docInfo;
	while (p != NULL) {
		if (p->docID == docID) {
			return p->times;
		}
		p = p->next;
	}
	return -1;
}

void word::modifyInfo(int docID, int times) {
	docNode *p;
	p = this->docInfo;
	while (p != NULL) {
		if (p->docID == docID) {
			p->times = times;
		}
		p = p->next;
	}
	return;
}
