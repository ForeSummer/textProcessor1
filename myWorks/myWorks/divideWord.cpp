#include "divideWord.h"
#include <math.h>

void initDictionaryInfo(Dic *myDic, string filePath) {
	ifstream inFs(filePath, ios::in);
	charString s;
	Node *node;
	string temp;
	while (!inFs.eof()) {
		getline(inFs, temp);
		s = charString(temp);
		node = new Node(s);
		myDic->dic[abs(s.line[0])].addStringNode(node);
	}
	return;
}

void divideWords(Song *mySong) {
	charString toDivide, lyric;
	lyric = mySong->lyrics;
	while (lyric.indexOf('\n') != lyric.length) {
		toDivide = lyric.subString(0, lyric.indexOf('\n'));
		//analyze toDivide
		lyric = lyric.subString(lyric.indexOf('\n') + 1, lyric.length);
	}
	toDivide = lyric;
	//analyze toDivide
}