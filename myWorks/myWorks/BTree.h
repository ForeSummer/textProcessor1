#ifndef BTREE_H
#define BTREE_H

#include "dic.h"

static const int M = 3;  
static const int KEY_MAX = 2*M-1;
static const int KEY_MIN = M-1;
static const int CHILD_MAX = KEY_MAX+1;
static const int CHILD_MIN = KEY_MIN+1;



class BTNode
{
public:
	int keyNum;
	word *key[KEY_MAX];
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
	Result searchBTree(string key); 
	void insertBTree(word* key);
	void printTree(string outputPath);
	BTree();
	~BTree();
private:

};

extern bool canFound(BTNode *p, word* key);

#endif