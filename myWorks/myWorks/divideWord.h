#ifndef DIVIDEWORD_H
#define DIVIDEWORD_H

#include "charString.h"
#include "song.h"
#include "stack.h"
#include "charStringLink.h"
#include <fstream>


class Dic
{
public:
	charStringLink dic[150];
public:
	bool isEqual(charString s);
	Dic(){};
};


extern void initDictionaryInfo(Dic *myDic, string filePath);

extern charStringLink* divideWords(Song *mySong, charStringLink *allWords, Dic *myDic, Dic *banList);

extern charString *getCNString(charString *s);

extern void analyzeString(charString *s, Dic *myDic, charStringLink *myLink, Dic *banList);


#endif