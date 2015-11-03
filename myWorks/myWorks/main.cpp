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
	charStringLink myLink;
	Song mySong = extractMusicInfoFromPage("0010.html");
	divideWords(&mySong, &myDic);
	return 0;
}