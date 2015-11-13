#include <iostream>
#include <fstream>
using namespace std;
#include "song.h"
#include "stack.h"
#include "charStringLink.h"
#include "divideWord.h"
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
	string configPath, inputPath, outputPath, dicPath, banListPath, myPath, temp;
	configPath = argv[1];
	inputPath = argv[2];
	outputPath = argv[3];
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
	charStringLink myLink[501], *allWords;
	Song mySong;
	//��ȡ������Ϣ�����зִ�
	for (int i = 0; i < size; i ++) {
		myPath = files[i];
		mySong = extractMusicInfoFromPage(myPath);
		temp = files[i].substr(inputPath.length(), files[i].length() - inputPath.length() - 5);
		myPath = outputPath + temp + out1;
		mySong.printSongInfo(myPath);
		allWords = divideWords(&mySong, &myLink[i], &myDic, &banList);
		myPath = outputPath + temp + out2;
		allWords->outPutList(myPath);
	}
	return 0;
}