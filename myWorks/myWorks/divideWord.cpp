#include "divideWord.h"
#include <math.h>

bool Dic::isEqual(charString s) {
	int length = this->dic[abs(s.line[0])].length;
	if (length == 0) {
		return false;
	}
	Node *p;
	p = this->dic[abs(s.line[0])].head;
	for (int i = 0; i < length; i ++) {
		if (s == p->data) {
			return true;
		}
		p = p->next;
	}
	return false;
}

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

charStringLink* divideWords(Song *mySong, charStringLink *allWords, Dic *myDic , Dic *banList) {
	charString toDivide, lyric;
	charString *CNString = NULL;
	lyric = mySong->lyrics;
	//歌词分成行再处理
	while (1) {
		toDivide = lyric.subString(0, lyric.indexOf('\n'));
		CNString = getCNString(&toDivide);
		analyzeString(CNString, myDic, allWords, banList);
		lyric = lyric.subString(lyric.indexOf('\n') + 1, lyric.length);
		if (lyric.indexOf('\n') == -1) {
			break;
		}
	}
	toDivide = lyric;
	CNString = getCNString(&toDivide);
	analyzeString(CNString, myDic, allWords, banList);
	return allWords;
}


charString *getCNString(charString *s) {
	//除去非中文字符
	int i = 0;
	while (i < s->length) {
		if (s->line[i] > 0) {
			s->deleteChar(i);
			continue;
		}
		if (s->length == 0) {
			break;
		}
		i ++;
	}
	return s;
}

void analyzeString(charString *s, Dic *myDic, charStringLink *myLink, Dic *banList) {
	if (s->length < 2) {
		return;
	}
	Node *p;
	charString temp;
	int startPos = 0, endPos = s->length;
	while (1) {
		temp = s->subString(startPos, endPos - startPos);
		if (endPos - startPos == 2 || myDic->isEqual(temp)) {
			if (!banList->isEqual(temp)) {
				p = new Node(temp);
				myLink->addStringNode(p);
			}
			if (endPos == s->length) {
				break;
			}
			startPos = endPos;
			endPos = s->length;
		}
		else {
			endPos = endPos - 2;
		}
	}
}
