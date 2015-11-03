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
	charStringLink dic[160];
public:
	Dic(){};
};


extern void initDictionaryInfo(Dic *myDic, string filePath);

extern void divideWords(Song *mySong, Dic *myDic);

extern charString *getCNString(charString *s);

extern bool isEqual(charString s, Dic *myDic);

extern void analyzeString(charString *s, Dic *myDic, charStringLink *myLink);

#endif