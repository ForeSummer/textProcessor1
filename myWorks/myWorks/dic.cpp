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

docNode::docNode() {
	this->docID = -1;
	this->times = 0;
	this->next = NULL;
}

void invertedFile::insertFile(string filePath) {
	ifstream inFs(filePath, ios::in);
	int docID;
	string temp;
	temp = filePath.substr(filePath.length() - 8, 4);
	docID = atoi(temp.c_str());
	Result myResult;
	word *myWord;
	while (!inFs.eof()) {
		getline(inFs,temp);
		myResult = this->myFile.searchBTree(temp);
		if (myResult.isFounded) {
			myWord = myResult.result->key[myResult.pos];
			myWord->addNewInfo(docID);
			myWord->occur ++;
		}
		else {
			myWord = new word();
			myWord->term = temp;
			this->myFile.insertBTree(myWord);
		}
	}
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
		}
	}
}

void invertedFile::saveFile(string filePath) {
	//out print BTree

}

void word::addNewInfo(int docID) {
	docNode *p;
	if (this->docInfo == NULL) {
		p = new docNode();
		p->docID = docID;
		p->times ++;
		this->DF ++;
		return;
	}
	p = this->docInfo;
	while (p->next != NULL) {
		if (p->docID == docID) {
			p->times ++;
			return;
		}
		p = p->next;
	}
	p->next = new docNode();
	p->next->docID = docID;
	p->next->times ++;
	this->DF ++;
}

invertedFile::invertedFile(string filePath) {
	//read tree from file
	ifstream inFs(filePath, ios::in);
	string temp;
	while (!inFs.eof()) {
		getline(inFs,temp);
		//get useful info
		//insert
	}
}