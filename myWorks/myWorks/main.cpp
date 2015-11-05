#include <iostream>
#include <fstream>
using namespace std;
#include "song.h"
#include "stack.h"
#include "charStringLink.h"
#include "divideWord.h"

int main(int argc, char *argv[]) {
	string configPath, inputPath, outputPath, dicPath, banListPath, myPath;
	configPath = argv[0];
	inputPath = argv[1];
	outputPath = argv[2];
	/*configPath = "E:\\课件\\大二上\\数据结构\\实验1材料\\pages\\info.config";
	inputPath = "E:\\课件\\大二上\\数据结构\\实验1材料\\pages";
	outputPath = inputPath;*/
	string addPath[10] = {"\\0001", "\\0002", "\\0003", "\\0004", "\\0005", "\\0006", "\\0007", "\\0008", "\\0009", "\\0010"};
	string in = ".html", out1 = ".info", out2 = ".txt";
	ifstream inFs(configPath, ios::in);
	getline(inFs, dicPath);
	getline(inFs, banListPath);
	Dic myDic, banList;
	initDictionaryInfo(&myDic, dicPath);
	initDictionaryInfo(&banList, banListPath);
	charStringLink myLink[10], *allWords;
	Song mySong;
	for (int i = 0; i < 10; i ++) {
		myPath = inputPath + addPath[i] + in;
		mySong = extractMusicInfoFromPage(myPath);
		myPath = outputPath + addPath[i] + out1;
		mySong.printSongInfo(myPath);
		allWords = divideWords(&mySong, &myLink[i], &myDic, &banList);
		myPath = outputPath + addPath[i] + out2;
		allWords->outPutList(myPath);
	}
	return 0;
}