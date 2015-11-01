#include "song.h"
#include <fstream>
using namespace std;


Song::Song() {}

Song::Song(Song &s) {
	this->title = s.title;
	this->singer = s.singer;
	this->album = s.album;
	this->publicDate = s.publicDate;
	this->lyricist = s.lyricist;
	this->composer = s.composer;
	this->lyrics = s.lyrics;
}

Song::~Song() {}

void Song::printSongInfo(string outputPath) {
	ofstream outFs(outputPath, ios::out);
	outFs << this->title.toString() << endl;
	outFs << this->singer.toString() << endl;
	outFs << this->album.toString() << endl;
	outFs << this->publicDate.toString() << endl;
	outFs << this->lyricist.toString() << endl;
	outFs << this->composer.toString() << endl;
	outFs << this->lyrics.toString() << endl;
	outFs.close();
}

Song& Song::operator = (const Song& s){
	this->title = s.title;
	this->singer = s.singer;
	this->album = s.album;
	this->publicDate = s.publicDate;
	this->lyricist = s.lyricist;
	this->composer = s.composer;
	this->lyrics = s.lyrics;
	return *this;
}

Song getSongInfo(string filePath) {
	ifstream inFs(filePath, ios::in);
	string match1 = "song_info_area", match2 = "music_list_area";
	charString matchString1 = charString(match1), matchString2 = charString(match2);
	charString s, info;
	string temp;
	while (1)
	{
		getline(inFs,temp);
		s = charString(temp);
		if(getPart(s, matchString1))	{
			break;
		}
	}
	while (1)
	{
		getline(inFs,temp);
		s = charString(temp);
		if(getPart(s, matchString2))	{
			break;
		}
		info.concat(s);
	}
	Song mySong = analyzeInfo(info);
	return mySong;
}

bool getPart(charString s, charString match) {
	int sameNum = 0;
	char ch = match.line[0];
	int i = 0;
	while (i < s.length)
	{
		if (ch == s.line[i]) {
			sameNum ++;
			i++;
		}
		else {
			i = i - sameNum + 1;
			sameNum = 0;
		}
		ch = match.line[sameNum];
		if (sameNum == match.length) {
			return true;
		}
	}
	return false;
}

Song analyzeInfo(charString s) {
	Song mySong;
	int pos = 0;
	return mySong;
}