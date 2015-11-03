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

void divideWords(Song *mySong, Dic *myDic) {
	charString toDivide, lyric;
	charString *CNString = NULL;
	charStringLink allWords;
	lyric = mySong->lyrics;
	while (1) {
		toDivide = lyric.subString(0, lyric.indexOf('\n'));
		CNString = getCNString(&toDivide);
		analyzeString(CNString, myDic, &allWords);
		lyric = lyric.subString(lyric.indexOf('\n') + 1, lyric.length);
		if (lyric.indexOf('\n') == -1) {
			break;
		}
	}
	toDivide = lyric;
	CNString = getCNString(&toDivide);
	analyzeString(CNString, myDic, &allWords);
	allWords.outPutList("out1.txt");
}

charString *getCNString(charString *s) {
	int i = 0;
	string s1 = "£¨", s2 = "£©", s3 = "£º", s4 = "¡«";
	while (i < s->length) {
		if (s->line[i] > 0) {
			s->deleteChar(i);
			continue;
		}
		else if(s->line[i] == s1[0] && s->line[i + 1] == s1[1]) {
			s->deleteChar(i);
			s->deleteChar(i);
			continue;
		}
		else if(s->line[i] == s2[0] && s->line[i + 1] == s2[1]) {
			s->deleteChar(i);
			s->deleteChar(i);
			continue;
		}
		else if(s->line[i] == s4[0] && s->line[i + 1] == s4[1]) {
			s->deleteChar(i);
			s->deleteChar(i);
			continue;
		}
		else if(s->line[i] == s3[0] && s->line[i + 1] == s3[1]) {
			for (int j = 0; j <= i + 1; j++) {
				s->deleteChar(0);
			}
			continue;
		}
		if (s->length == 0) {
			break;
		}
		i ++;
	}
	return s;
}

bool isEqual(charString s, Dic *myDic) {
	int length = myDic->dic[abs(s.line[0])].length;
	if (length == 0) {
		return false;
	}
	Node *p;
	p = myDic->dic[abs(s.line[0])].head;
	for (int i = 0; i < length; i ++) {
		if (s == p->data) {
			return true;
		}
		p = p->next;
	}
	return false;
}

void analyzeString(charString *s, Dic *myDic, charStringLink *myLink) {
	if (s->length < 2) {
		return;
	}
	Node *p;
	charString temp;
	int startPos = 0, endPos = s->length;
	while (1) {
		temp = s->subString(startPos, endPos - startPos);
		if (endPos - startPos == 2 || isEqual(temp, myDic)) {
			p = new Node(temp);
			myLink->addStringNode(p);
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