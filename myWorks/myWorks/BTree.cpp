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
	if (root == NULL) {
		return;
	}
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

Result BTree::searchBTree(charString key) {
	Result searchResult(NULL, 0, 0);
	BTNode *p;
	p = this->root;
	if (p == NULL) {
		return searchResult;
	}
	while(true){
		int pos = 0;
		while (pos != p->keyNum && p->key[pos]->term < key)
			pos ++;
		if(pos != p->keyNum && key == p->key[pos]->term) {
			searchResult.isFounded = 1;
			searchResult.pos = pos;
			searchResult.result = p;
			return searchResult;
		}
		else{
			if(p->leaf){
				return searchResult;
			}
			else
				p = p->ptr[pos];
		}
	}
	/*while (!p->leaf) {
		if (key < p->key[0]->term) {
			p = p->ptr[0];
		}
		else if (key > p->key[p->keyNum - 1]->term) {
			p = p->ptr[p->keyNum];
		}
		else if (key == p->key[p->keyNum - 1]->term) {
			searchResult.isFounded = 1;
			searchResult.pos = p->keyNum - 1;
			searchResult.result = p;
		}
		else {
			for (int i = 0; i < p->keyNum - 1; i++) {
				if (key == p->key[i]->term) {
					searchResult.isFounded = 1;
					searchResult.pos = i;
					searchResult.result = p;
				}
				if (key > p->key[i]->term && key < p->key[i + 1]->term) {
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
	return searchResult;*/
}

void BTree::printTree(string outputPath) {
	ofstream outFs(outputPath, ios::out);
	queue<BTNode*> myQueue;
	word *myWord;
	docNode *info;
	myQueue.push(this->root);
	BTNode* p;
	while (!myQueue.empty()) {
		p = myQueue.front();
		if (p->leaf) {
			for (int i = 0; i < p->keyNum; i ++) {
				myWord = p->key[i];
				outFs << '{' << myWord->term.toString() << ',' << myWord->DF << ',' << myWord->occur << '}';
				info = myWord->docInfo;
				while (info != NULL) {
					outFs << " {" << info->docID << ',' << info->times << '}';
					info = info->next;
				}
				outFs << endl;
			}
			myQueue.pop();
		}
		else {
			for (int i = 0; i < p->keyNum; i ++) {
				myWord = p->key[i];
				outFs << '{' << myWord->term.toString() << ',' << myWord->DF << ',' << myWord->occur << '}';
				info = myWord->docInfo;
				while (info != NULL) {
					outFs << " {" << info->docID << ',' << info->times << '}';
					info = info->next;
				}
				outFs << endl;
			}
			for (int i = 0; i <= p->keyNum; i ++) {
				myQueue.push(p->ptr[i]);
			}
			myQueue.pop();
		}
	}
}


void invertedFile::insertFile(string filePath) {
	ifstream inFs(filePath, ios::in);
	int docID;
	string temp;
	charString *line, *ID;
	line = new charString(filePath);
	*ID = line->subString(line->length - 8, 4);
	cout << line->toString()<<endl;
	docID = atoi(ID->line);
	Result myResult;
	word *myWord;
	while (!inFs.eof()) {
		getline(inFs,temp);
		delete line;
		line = new charString(temp);
		//cout << temp<<endl;
		myResult = this->myFile.searchBTree(*line);
		if (myResult.isFounded) {
			myWord = myResult.result->key[myResult.pos];
			myWord->addNewInfo(docID);
			myWord->occur ++;
		}
		else {
			myWord = new word();
			myWord->term = temp;
			myWord->occur ++;
			myWord->addNewInfo(docID);
			this->myFile.insertBTree(myWord);
		}
	}
	delete line;
}

void invertedFile::buildFile(string path) {
	vector<string> files;
	long hFile = 0;
	struct _finddata_t fileinfo;
	string p, temp;
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
		do {
			if(strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0){
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		}while(_findnext(hFile, &fileinfo)  == 0);
		_findclose(hFile);
	}
	for (int i = 0; i < files.size(); i++) {
		temp = files[i];
		if (temp[temp.length() - 1] == 't') {
			this->insertFile(files[i]);
			cout << temp<<endl;
		}
	}
}

void invertedFile::saveFile(string filePath) {
	this->myFile.printTree(filePath);
}

/*invertedFile::invertedFile(string filePath) {
	//read tree from file
	ifstream inFs(filePath, ios::in);
	string temp;
	while (!inFs.eof()) {
		getline(inFs,temp);
		//get useful info
		//insert
	}
}*/