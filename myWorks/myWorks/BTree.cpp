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
	charString *line, ID;
	line = new charString(filePath);
	ID = line->subString(line->length - 8, 4);
	docID = atoi(ID.line);
	Result myResult;
	word *myWord;
	while (!inFs.eof()) {
		getline(inFs,temp);
		delete line;
		line = new charString(temp);
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
			//cout << temp << endl;
		}
	}
}

void invertedFile::saveFile(string filePath) {
	this->myFile.printTree(filePath);
}

void invertedFile::loadFile(string filePath) {
	ifstream inFs(filePath, ios::in);
	int startPos = 0, endPos = 0, number, count = 0;
	string temp;
	charString* line;
	charString num;
	word* myWord;
	docNode* p, *pre = NULL;
	while (!inFs.eof()) {
		getline(inFs, temp);
		//delete line;
		line = new charString(temp);
		for (int i = 0; i < line->length; i ++) {
			if (line->line[i] == '{') {
				startPos = i + 1;
			}
			else if (line->line[i] == '}' || line->line[i] == ',') {
				endPos = i;
				num = line->subString(startPos, endPos - startPos);
				startPos = i + 1;
				if (count == 0) {
					myWord = new word();
					myWord->term = num;
					count ++;
				}
				else {
					number = atoi(num.line);
					if (count == 1) {
						myWord->DF = number;
						count ++;
					}
					else if (count == 2) {
						myWord->occur = number;
						count ++;
					}
					else {
						if (count % 2 == 1) {
							p = new docNode();
							p->docID = number;
							count ++;
						}
						else {
							p->times = number;
							if (pre == NULL) {
								myWord->docInfo = p;
							}
							else {
								pre->next = p;
							}
							pre = p;
							count ++;
						}
					}
				}
			}
		}
		pre = NULL;
		startPos = endPos = count = 0;
		this->myFile.insertBTree(myWord);
	}
}

void invertedFile::getRelativeRank(int i, int* rank) {
	queue<BTNode*> myQueue;
	word *myWord;
	docNode *info;
	myQueue.push(this->myFile.root);
	int existFlag = 0;
	int times = 0;
	BTNode* p;
	while (!myQueue.empty()) {
		p = myQueue.front();
		if (p->leaf) {
			for (int i = 0; i < p->keyNum; i ++) {
				myWord = p->key[i];
				info = myWord->docInfo;
				while (info != NULL) {
					if (info->docID == i) {
						existFlag = 1;
						times = info->times;
						break;
					}
					info = info->next;
				}
				info = myWord->docInfo;
				if (existFlag) {
					while (info != NULL) {
						if (info->docID != i) {
							rank[info->docID - 1] += times * info->times;
						}
						info = info->next;
					}
				}
				existFlag = 0;
			}
			myQueue.pop();
		}
		else {
			for (int i = 0; i < p->keyNum; i ++) {
				myWord = p->key[i];
				info = myWord->docInfo;
				while (info != NULL) {
					if (info->docID == i) {
						existFlag = 1;
						times = info->times;
						break;
					}
					info = info->next;
				}
				info = myWord->docInfo;
				if (existFlag) {
					while (info != NULL) {
						if (info->docID != i) {
							rank[info->docID - 1] += times * info->times;
						}
						info = info->next;
					}
				}
				existFlag = 0;
			}
			for (int i = 0; i <= p->keyNum; i ++) {
				myQueue.push(p->ptr[i]);
			}
			myQueue.pop();
		}
	}
}

void BTree::searchInfo(charString key, Dic *myDic, Dic *banlist, string outputPath, int status) {
	int startPos = 0, endPos = 0, flag = 0, count = 0, length = 0;
	vector<record> result;
	record* re;
	Result info;
	charStringLink allWords;
	word* myWord;
	docNode *p;
	charString temp;
	//divide key words
	for (int i = 0; i < key.length; i ++) {
		if (key.line[i] == ' ') {
			endPos = i;
			temp = key.subString(startPos, endPos - startPos);
			analyzeString(&temp, myDic, &allWords, banlist);
			startPos = i + 1;
		}
	}
	endPos = key.length;
	temp = key.subString(startPos, endPos - startPos);
	analyzeString(&temp, myDic, &allWords, banlist);
	//search
	Node *a;
	a = allWords.head;
	while (a != NULL) {
		info = this->searchBTree(a->data);
		if (info.isFounded) {
			myWord = info.result->key[info.pos];
			p = myWord->docInfo;
			while (p != NULL) {
				for (int i = 0; i < result.size(); i ++) {
					if (p->docID == result[i].docID) {
						result[i].fitNum ++;
						result[i].times += p->times;
						flag = 1;
					}
				}
				if (flag == 0) {
					re =new record();
					re->docID = p->docID;
					re->fitNum ++;
					re->times = p->times;
					result.push_back(*re);
					delete re;
				}
				flag = 0;
				p = p->next;
			}
		}
		a = a->next;
	}

	//sort and output result
	sort(result.begin(),result.end());
	ofstream outFs(outputPath, ios::out | ios::app);
	length = result.size();
	if (length != 0) {
		count = result[0].fitNum;
		for (int i = length - 1; i >= 0; i --) {
			if (result[i].fitNum != count) {
				result.pop_back();
			}
			else {
				break;
			}
		}
	}
	if (status == 0) {
		for (int i = 0; i < result.size(); i ++) {
			outFs << "(" <<result[i].docID << "," << result[i].times << ") ";
		}
		if(result.size() == 0) {
			outFs << "未找到相关歌曲" << endl;
		}
		else {
			outFs << endl;
		}
	}
	else {
		for (int i = 0; i < result.size(); i ++) {
			cout << "(" <<result[i].docID << "," << result[i].times << ") ";
		}
		if(result.size() == 0) {
			cout << "未找到相关歌曲" << endl;
		}
		else {
			cout << endl;
		}
	}
	outFs.close();
}

record::record() {
	this->docID = -1;
	this->fitNum = 0;
	this->times = 0;
}

bool record::operator== (const record &s) const{
	if (this->fitNum != s.fitNum) {
		return false;
	}
	if (this->times != s.times) {
		return false;
	}
	return true;
}

bool record::operator> (const record &s) const{
	if (this->fitNum < s.fitNum) {
		return true;
	}
	else if (this->fitNum == s.fitNum) {
		if (this->times < s.times) {
			return true;
		}
	}
	return false;
}

bool record::operator< (const record &s) const{
	if (this->fitNum > s.fitNum) {
		return true;
	}
	else if (this->fitNum == s.fitNum) {
		if (this->times > s.times) {
			return true;
		}
	}
	return false;
}