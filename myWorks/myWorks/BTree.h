#ifndef BTREE_H
#define BTREE_H

static const int M = 3;  
static const int KEY_MAX = 2*M-1;
static const int KEY_MIN = M-1;
static const int CHILD_MAX = KEY_MAX+1;
static const int CHILD_MIN = KEY_MIN+1;



class BTNode
{
public:
	int keyNum;
	int key[KEY_MAX];
	bool leaf;
	BTNode *parent;
	BTNode *ptr[CHILD_MAX];
	BTNode();
	void splitNode(int index);
	void normalInsert(int key);
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
	Result searchBTree(int key); 
	void insertBTree(int key);
	void printTree();
	BTree();
	~BTree();
private:

};

extern bool canFound(BTNode *p, int key);

#endif