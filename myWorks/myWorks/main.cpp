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
		outFs << "δ�ҵ���������" << endl;
		return;
	}
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
}

int main(/*int argc, char *argv[]*/) {
	string configPath, inputPath, outputPath, dicPath, banListPath, myPath, temp, lyricInfoPath, queryPath, resultPath, recommandPath, result2Path;
	invertedFile lyricInfo;
	configPath = "E://test//info.config";
	inputPath = "E://input";
	outputPath = "E://output";
	lyricInfoPath = "E://lyric.info";
	queryPath = "E://test//query1.txt";
	resultPath = "E://result1.txt";	
	recommandPath = "E://test//query2.txt";
	result2Path = "E://result2.txt";
	vector<string> files;
	getFiles(inputPath, files);
	int size = files.size();
	string out1 = ".info", out2 = ".txt";

	//����config��Ϣ

	ifstream inFs(configPath, ios::in);
	getline(inFs, dicPath);
	getline(inFs, banListPath);
	inFs.close();

	//���벢��ʼ���ʿ�ͽ��ôʱ�

	Dic myDic, banList;
	initDictionaryInfo(&myDic, dicPath);
	initDictionaryInfo(&banList, banListPath);
	charStringLink *allWords;
	Song mySong[300];

	//��ȡ������Ϣ�����зִ�
	for (int i = 0; i < size; i ++) {
		myPath = files[i];
		charStringLink myLink;
		temp = files[i].substr(inputPath.length(), files[i].length() - inputPath.length() - 5);
		cout << "Now Loading " << files[i].substr(inputPath.length(), files[i].length() - inputPath.length()) << "..." << endl;
		mySong[i] = extractMusicInfoFromPage(myPath);
		cout << mySong[i].title.toString() << endl;
		myPath = outputPath + temp + out1;
		mySong[i].printSongInfo(myPath);
		allWords = divideWords(&mySong[i], &myLink, &myDic, &banList);
		myPath = outputPath + temp + out2;
		allWords->outPutList(myPath);
		cout << "Loading Success" << endl;
	}

	
	//���ݷִʽ�����������ĵ�
	lyricInfo.buildFile(outputPath);
	
	//���������ĵ�
	/*ifstream searchIn(queryPath, ios::in);
	while (!searchIn.eof()) {
		getline(searchIn, temp);
		cout << temp <<endl;
		lyricInfo.myFile.searchInfo(temp, &myDic, &banList, resultPath, 0);
	}
	searchIn.close();*/

	//�Ƽ�����
	ifstream recommandIn(recommandPath, ios::in);
	ofstream outFs(outputPath, ios::out);
	outFs << "recommand result:" << endl;
	outFs.close();
	while (!recommandIn.eof()) {
		getline(recommandIn, temp);
		getRecommand(temp, result2Path, mySong, &lyricInfo);
	}
	recommandIn.close();

	//gui
	/*string input;
	charString *toSearch;
	while (1) {
		cout << "������ؼ��ʣ��ؼ���֮���ÿո�������˳������롰#�����س�����������..." << endl;
		cin >> input;
		if (input[0] == '#') {
			break;
		}
		toSearch = new charString(input);
		lyricInfo.myFile.searchInfo(*toSearch, &myDic, &banList, resultPath, 1);
	}*/

	//lyricInfo.saveFile(lyricInfoPath);*/
	return 0;
}