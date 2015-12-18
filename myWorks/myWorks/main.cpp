#include <iostream>
#include <fstream>
using namespace std;
#include "song.h"
#include "stack.h"
#include "charStringLink.h"
#include "divideWord.h"
#include "BTree.h"
#include <io.h>
#include <vector>


//the function below is from http://blog.csdn.net/xuejiren/article/details/37040827 to get all files of a folder
void getFiles(string path, vector<string>& files) {
	long hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
		do {
			if(strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0){
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		}while(_findnext(hFile, &fileinfo)  == 0);
		_findclose(hFile);
	}
}

int main(int argc, char *argv[]) {
	string configPath, inputPath, outputPath, dicPath, banListPath, myPath, temp, lyricInfoPath, mainInfoPath, queryPath, resultPath;
	invertedFile mainInfo, lyricInfo;
	configPath = "info.config";
	inputPath = "pages_300";
	outputPath = "pages_300";
	lyricInfoPath = "lyric.info";
	mainInfoPath = "main.info";
	queryPath = "query1.txt";
	resultPath = "result1.txt";
	vector<string> files;
	getFiles(inputPath, files);
	int size = files.size();
	string out1 = ".info", out2 = ".txt", out3 = ".main";

	//读入config信息

	ifstream inFs(configPath, ios::in);
	getline(inFs, dicPath);
	getline(inFs, banListPath);
	inFs.close();

	//读入并初始化词库和禁用词表

	Dic myDic, banList;
	initDictionaryInfo(&myDic, dicPath);
	initDictionaryInfo(&banList, banListPath);
	charStringLink myLink[400], *allWords, mainLink[400];
	Song mySong;

	//提取歌曲信息并进行分词
	for (int i = 0; i < size; i ++) {
		myPath = files[i];
		temp = files[i].substr(inputPath.length(), files[i].length() - inputPath.length() - 5);
		cout << "Now Loading " << files[i].substr(inputPath.length(), files[i].length() - inputPath.length()) << "..." << endl;
		mySong = extractMusicInfoFromPage(myPath);
		myPath = outputPath + temp + out1;
		mySong.printSongInfo(myPath);
		allWords = divideWords(&mySong, &myLink[i], &myDic, &banList);
		myPath = outputPath + temp + out2;
		allWords->outPutList(myPath);
		myPath = outputPath + temp + out3;
		allWords = getMainWords(&mySong, &mainLink[i], &myDic, &banList);
		allWords->outPutList(myPath);
		cout << "Loading Success" << endl;
	}

	//根据分词结果构建倒排文档
	mainInfo.buildMainFile(inputPath);
	lyricInfo.buildFile(inputPath);
	
	//处理搜索文档
	ifstream searchIn(queryPath, ios::in);
	while (!searchIn.eof()) {
		getline(searchIn, temp);
		mainInfo.myFile.searchInfo(temp, &myDic, &banList, resultPath);
		lyricInfo.myFile.searchInfo(temp, &myDic, &banList, resultPath);
	}
	lyricInfo.saveFile(lyricInfoPath);
	mainInfo.saveFile(mainInfoPath);
	return 0;
}