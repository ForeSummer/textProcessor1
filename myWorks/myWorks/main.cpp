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

//推荐算法
void getRecommand(charString line, string outputPath, Song* allSong, invertedFile *myFile) {
	int pos = -1;
	int recommand[10], recommandNum = 0;
	ofstream outFs(outputPath, ios::out | ios::app);
	int rank[300] = {0};
	charString singer;
	for (int i = 0; i < 300; i ++) {
		if (getPart(line, allSong[i].title)) {
			pos = i;
		}
	}
	if (pos == -1) {
		outFs << "未找到输入音乐" << endl;
		return;
	}
	//优先找到至多5个同歌手歌曲
	singer = allSong[pos].singer;
	for (int i = 0; i < 300; i ++) {
		if (i == pos) {
			continue;
		}
		if (recommandNum >= 5) {
			break;
		}
		if (singer == allSong[i].singer) {
			recommand[recommandNum] = i + 1;
			recommandNum ++;
		}
	}
	//根据相关度匹配满10个歌曲
	myFile->getRelativeRank(pos + 1, rank);
	int leftNum = 10 - recommandNum;
	int max = 0, maxPos = 0;
	while (leftNum > 0) {
		for (int i = 0; i < 300;i ++) {
			if (rank[i] > max) {
				maxPos = i + 1;
				max = rank[i];
				rank[i] = -1;
			}
		}
		recommand[recommandNum] = maxPos;
		recommandNum ++;
		leftNum --;
		max = 0;
		maxPos = 0;
	}
	
	for (int i = 0; i < recommandNum; i ++) {
		outFs << "{" << recommand[i] << "," << allSong[recommand[i] - 1].title.toString() << "}";
	}
	outFs << endl;
	outFs.close();
}

int main(/*int argc, char *argv[]*/) {
	string configPath, inputPath, outputPath, dicPath, banListPath, myPath, temp, lyricInfoPath, queryPath, resultPath, recommandPath, result2Path;
	invertedFile lyricInfo;
	configPath = "info.config";
	inputPath = "pages_300";
	outputPath = "output_300";
	lyricInfoPath = "lyric.info";
	queryPath = "query1.txt";
	resultPath = "result1.txt";	
	recommandPath = "query2.txt";
	result2Path = "result2.txt";
	vector<string> files;
	getFiles(inputPath, files);
	int size = files.size();
	string out1 = ".info", out2 = ".txt";

	//读入config信息

	ifstream inFs(configPath, ios::in);
	getline(inFs, dicPath);
	getline(inFs, banListPath);
	inFs.close();

	//读入并初始化词库和禁用词表

	Dic myDic, banList;
	cout << "Now loading Dic... ";
	initDictionaryInfo(&myDic, dicPath);
	initDictionaryInfo(&banList, banListPath);
	cout << "Loading Success" << endl;
	charStringLink *allWords;
	Song mySong[300];

	//提取歌曲信息并进行分词
	for (int i = 0; i < size; i ++) {
		myPath = files[i];
		charStringLink myLink;
		temp = files[i].substr(inputPath.length(), files[i].length() - inputPath.length() - 5);
		cout << "Now Loading " << files[i].substr(inputPath.length(), files[i].length() - inputPath.length()) << "..." ;
		mySong[i] = extractMusicInfoFromPage(myPath);
		cout << mySong[i].title.toString();
		myPath = outputPath + temp + out1;
		mySong[i].printSongInfo(myPath);
		allWords = divideWords(&mySong[i], &myLink, &myDic, &banList);
		myPath = outputPath + temp + out2;
		allWords->outPutList(myPath);
		cout << "Loading Success" << endl;
	}

	
	//根据分词结果构建倒排文档
	cout << "Now loading inverted file";
	lyricInfo.buildFile(outputPath);
	cout << "Loading Success" << endl;

	ifstream searchIn(queryPath, ios::in);
	ifstream recommandIn(recommandPath, ios::in);
	ofstream outFs(result2Path, ios::out);
	string input;
	charString *toSearch;

	int taskId = 3; 
	switch (taskId){ 
	case 1:
		//处理搜索文档
		cout << "Now processing..." << endl;
		while (!searchIn.eof()) {
			getline(searchIn, temp);
			toSearch = new charString(temp);
			lyricInfo.myFile.searchInfo(*toSearch, &myDic, &banList, resultPath, 0);
		}
		searchIn.close();
		cout << "Success" << endl;
		break; 
	case 2:
		//推荐歌曲
		cout << "Now processing..." << endl;
		outFs << "recommand result:" << endl;
		outFs.close();
		while (!recommandIn.eof()) {
			getline(recommandIn, temp);
			toSearch = new charString(temp);
			getRecommand(*toSearch, result2Path, mySong, &lyricInfo);
		}
		recommandIn.close();
		cout << "Success" << endl;
		break; 
	case 3: 
		//gui
		while (1) {
			cout << "请输入关键词，关键词之间用空格隔开，退出请输入“#”，回车键发起搜索..." << endl;
			cin >> input;
			if (input[0] == '#') {
				break;
			}
			toSearch = new charString(input);
			lyricInfo.myFile.searchInfo(*toSearch, &myDic, &banList, resultPath, 1);
		}
		break; 
	default: 
		break; 
	}
	return 0;
}