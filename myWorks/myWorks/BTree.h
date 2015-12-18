#ifndef BTREE_H
#define BTREE_H

#include "dic.h"
#include <io.h>
#include <vector>
#include <utility>

static const int M = 15;  
static const int KEY_MAX = 2*M-1;
static const int KEY_MIN = M-1;
static const int CHILD_MAX = KEY_MAX+1;
static const int CHILD_MIN = KEY_MIN+1;



class BTNode
{
public:
	int keyNum;
	word* key[KEY_MAX];
	bool leaf;
	BTNode *parent;
	BTNode *ptr[CHILD_MAX];
	BTNode();
	void splitNode(int index);
	void normalInsert(word* key);
};

class Result
{
public:
	BTNode *result;
	int pos;
	int isFounded;
	Result();
	Result(BTNode *result, int pos, int isFounded);
};

class BTree
{
public:
	BTNode *root;
	Result searchBTree(charString key); 
	void insertBTree(word* key);
	void printTree(string outputPath);
	void searchInfo(charString key);
	BTree();
	~BTree();
private:

};

class invertedFile
{
public:
	BTree myFile;
	void buildFile(string path);
	void insertFile(string filePath);
	void saveFile(string filePath);
	void loadFile(string filePath);
};

class record
{
public:
	int docID;
	int times;
	int fitNum;
	record();
	bool operator == (const record& s) const;
	bool operator < (const record& s) const;
	bool operator > (const record& s) const;
};

#endif