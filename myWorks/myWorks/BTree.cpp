#include "BTree.h"
#include <iostream>
#include <queue>
#include <stack>
#include <fstream>
using namespace std;


BTNode::BTNode() {
	keyNum = 0;
	parent = NULL;
	for (int i = 0; i <= M; i++) {
		key[i] = NULL;
		ptr[i] = NULL;
	}
	leaf = true;
}

BTree::BTree() {
	root = NULL; 
}

BTree::~BTree() {
	stack<BTNode*> myStack;
	myStack.push(this->root);
	BTNode* p;
	while (!myStack.empty()) {
		p = myStack.top();
		if (p != NULL && p->leaf) {
			delete p;
			p = NULL;
			myStack.pop();
		}
		else {
			for (int i = 0; i <= p->keyNum; i ++) {
				myStack.push(p->ptr[i]);
				p->leaf = true; 
			}
		}
	}
}

Result::Result() {
	result = NULL;
	pos = -1;
	isFounded = -1;
}

Result::Result(BTNode *result, int pos, int isFounded) {
	this->result = result;
	this->pos = pos;
	this->isFounded = isFounded;
}

void BTNode::normalInsert(word* key) {
	BTNode *p;
	int i = this->keyNum;
	if (this->leaf) {
		while (i > 0 && key->term < this->key[i - 1]->term) {
			this->key[i] = this->key[i - 1];
			i --;
		}
		this->key[i] = key;
		this->keyNum ++;
	}
	else {
		while (i > 0 && key->term < this->key[i - 1]->term) {
			i --;
		}
		p = this->ptr[i];
		if (p->keyNum == KEY_MAX) {
			p->parent = this;
			p->splitNode(i);
			if(key->term > this->key[i]->term)


				p = this->ptr[i + 1];  
		}
		p->normalInsert(key);
	}
}

void BTNode::splitNode(int index) {
	BTNode *p = new BTNode();
	p->leaf = this->leaf;
	p->keyNum = KEY_MIN;
	for (int i = 0; i < KEY_MIN; i ++) {  
		p->key[i] = this->key[i+CHILD_MIN];  
	}  
	if (!this->leaf) {  
		for (int i = 0; i < CHILD_MIN; i ++) {  
			p->ptr[i] = this->ptr[i+CHILD_MIN];  
		}  
	}  
	this->keyNum = KEY_MIN;
	for (int i = this->parent->keyNum; i > index; i --) {  
		this->parent->ptr[i + 1] = this->parent->ptr[i];  
		this->parent->key[i] = this->parent->key[i - 1];  
	}
	this->parent->keyNum ++;
	this->parent->ptr[index + 1] = p;
	this->parent->key[index] = this->key[KEY_MIN];
}

void BTree::insertBTree(word* key) {
	BTNode *p;
	if (canFound(this->root, key)) {
		return;
	}
	if (this->root == NULL) {
		root = new BTNode();
	}
	if(this->root->keyNum == KEY_MAX) {
		p = new BTNode();
		p->leaf = false;
		p->ptr[0] = root;
		root->parent = p;
		root->splitNode(0);
		root = p;
	}
	root->normalInsert(key);
}

Result BTree::searchBTree(string key) {
	Result searchResult(NULL, 0, 0);
	BTNode *p;
	p = this->root;
	while (!p->leaf) {
		if (key < p->key[0]->term) {
			p = p->ptr[0];
		}
		else if (key > p->key[p->keyNum - 1]->term) {
			p = p->ptr[p->keyNum];
		}
		else {
			for (int i = 0; i < p->keyNum; i++) {
				if (key >= p->key[i]->term && key < p->key[i + 1]->term) {
					p = p->ptr[i + 1];
				}
			}
		}
	}
	for (int i = 0; i < p->keyNum; i++) {
		if (key == p->key[i]->term) {
			searchResult.isFounded = 1;
			searchResult.pos = i;
			searchResult.result = p;
			return searchResult;
		}
	}
	return searchResult;
}

bool canFound(BTNode *p, word* key) {
	if (p == NULL) {  
		return false;  
	}
	else  {  
		int pos;
		if (key->term < p->key[0]->term) {
			pos = 0;
		}
		else if(key->term > p->key[p->keyNum - 1]->term) {
			pos = p->keyNum;
		}
		else {
			for (int i = 0; i < p->keyNum - 1; i ++) {
				if (key->term == p->key[i]->term) {
					return true;
				}
				if (key->term > p->key[i]->term && key->term < p->key[i + 1]->term) {
					pos = i + 1;
					break;
				}
			}
		}
		if (p->leaf) {  
			return false;  
		}  
		else {  
			return canFound(p->ptr[pos], key);  
		}
	}  
}

void BTree::printTree(string outputPath) {
	ofstream outFs(outputPath, ios::out);
	//orgnize info
	queue<BTNode*> myQueue;
	myQueue.push(this->root);
	BTNode* p;
	while (!myQueue.empty()) {
		p = myQueue.front();
		if (p->leaf) {
			for (int i = 0; i < p->keyNum; i ++) {
				cout << p->key[i] << " ";
			}
			cout << endl;
			myQueue.pop();
		}
		else {
			for (int i = 0; i < p->keyNum; i ++) {
				cout << p->key[i] << " ";
			}
			cout << endl;
			for (int i = 0; i <= p->keyNum; i ++) {
				myQueue.push(p->ptr[i]);
			}
			myQueue.pop();
		}
	}
}