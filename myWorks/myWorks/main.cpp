#include <iostream>
#include <fstream>
using namespace std;
#include "song.h"
#include "stack.h"
#include "charStringLink.h"
#include "divideWord.h"

int main() {
	string filePath = "´Ê¿â.dic";
	Dic myDic;
	initDictionaryInfo(&myDic, filePath);
	for (int i = 0; i < 160; i ++)
	{
		cout <<myDic.dic[i].length<<endl;
	}
	/*Song mySong = extractMusicInfoFromPage(filePath);
	charStringLink c;
	Node *node;
	node = new Node(mySong.album);
	c.addStringNode(node);
	node = new Node(mySong.composer);
	c.addStringNode(node);
	node = new Node(mySong.lyricist);
	c.addStringNode(node);
	//c.deleteStringNode(2);
	c.outPutList("out1.txt");
	//mySong.printSongInfo("out.txt");*/
	return 0;
}