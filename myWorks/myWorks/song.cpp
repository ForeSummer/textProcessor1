#include "song.h"
#include "stack.h"
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
	if (this->lyricist.line[0] != '#') {
		outFs << this->lyricist.toString() << endl;
	}
	if (this->composer.line[0] != '#') {
		outFs << this->composer.toString() << endl;
	}
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
			info = info.concat(s);
			break;
		}
	}
	while (1)
	{
		getline(inFs,temp);
		temp = temp + '\n';
		s = charString(temp);
		if(getPart(s, matchString2))	{
			break;
		}
		info = info.concat(s);
	}
	inFs.close();
	Song mySong = analyzeInfo(&info);
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

Song analyzeInfo(charString *s) {
	Song mySong;
	Stack myStack;
	myStack.initStack();
	Node *temp = NULL;
	charString tempString;
	int liNum = 0;
	int titleStart = 0, titleEnd = 0;
	int singerStart = 0, singerEnd = 0;
	int albumStart = 0, albumEnd = 0;
	int dateStart = 0, dateEnd = 0;
	int lyriclistStart = 0, lyriclistEnd = 0;
	int composerStart = 0, composerEnd = 0;
	int lyricStart = 0, lyricEnd = 0;
	string div = "div", h2 = "h2", a = "a", ul = "ul", li = "li", script = "script", span = "span", p = "p", textarea = "textarea", lyriclist = "´Ê", composer = "Çú", colonInCN = "£º", none = "#";
	charString lyriclistString(lyriclist), composerString(composer), colonCNString(colonInCN);
	//cout <<composerString.length<<endl;
	int pos = 0;
	while (pos < s->length) {
		if (s->line[pos] == '<') {
			if (s->line[pos + 1] == '/') {
				switch (s->line[pos + 2])
				{
				case 'd':
					if (myStack.top->data.line[0] == 'd') {
						if (!myStack.isEmpty()) {
							myStack.pop();
						}
					}
					break;
				case 'h':
					if (myStack.top->data.line[0] == 'h') {
						myStack.pop();
					}
					break;
				case 'a':
					if (myStack.top->data.line[0] == 'a') {
						if (liNum == 1) {
							singerEnd = pos;
							mySong.singer = s->subString(singerStart, singerEnd - singerStart);
							//cout << mySong.singer.toString()<<endl;
						}
						else if (liNum == 3) {
							albumEnd = pos;
							mySong.album = s->subString(albumStart, albumEnd - albumStart);
							//cout << mySong.album.toString()<<endl;
						}
						myStack.pop();
					}
					break;
				case 'u':
					if (myStack.top->data.line[0] == 'u') {
						myStack.pop();
					}
					break;
				case 'l':
					if (myStack.top->data.line[0] == 'l') {
						myStack.pop();
					}
					break;
				case 's':
					if (s->line[pos + 3] == 'p') {
						if (myStack.top->data.line[0] == 's' && myStack.top->data.line[1] == 'p') {
							if (liNum == 4) {
								dateEnd = pos;
								mySong.publicDate = s->subString(dateStart, dateEnd - dateStart);
								//cout << mySong.publicDate.toString()<<endl;
								liNum = 0;
							}
							myStack.pop();
						}
					}
					else {
						if (myStack.top->data.line[0] == 's' && myStack.top->data.line[1] == 'c') {
							myStack.pop();
						}
					}
					break;
				case 'p':
					if (myStack.top->data.line[0] == 'p') {
						myStack.pop();
						if (composerStart != 0) {
							composerEnd = pos;
							mySong.composer = s->subString(composerStart, composerEnd - composerStart);
							//cout << mySong.composer.toString()<<endl;
							composerStart = 0;
						}
						else if (lyriclistStart != 0) {
							lyriclistEnd = pos;
							mySong.lyricist = s->subString(lyriclistStart, lyriclistEnd - lyriclistStart);
							//cout << mySong.lyricist.toString()<<endl;
							lyriclistStart = 0;
						}
					}
					break;
				case 't':
					if (myStack.top->data.line[0] == 't') {
						lyricEnd = pos;
						mySong.lyrics = s->subString(lyricStart, lyricEnd - lyricStart - 1);
						//cout << mySong.lyrics.toString()<<endl;
						myStack.pop();
					}
					break;
				}
				pos = pos + 2;
				//check stack top,then pop stack
			}
			else {
				switch (s->line[pos + 1])
				{
				case 'd':
					tempString = charString(div);
					temp = new Node(tempString);
					myStack.push(temp);
					break;
				case 'h':
					tempString = charString(h2);
					temp = new Node(tempString);
					myStack.push(temp);
					//get title info
					titleStart = titleEnd = pos + 11;
					while (1) {
						titleEnd ++;
						if (s->line[titleEnd] == '"') {
							break;
						}
					}
					pos = titleEnd;
					mySong.title = s->subString(titleStart, titleEnd - titleStart);
					//cout << mySong.title.toString()<<endl;
					break;
				case 'a':
					tempString = charString(a);
					temp = new Node(tempString);
					myStack.push(temp);
					//top .next ==li singer
					//top.next == li album
					break;
				case 'u':
					tempString = charString(ul);
					temp = new Node(tempString);
					myStack.push(temp);
					break;
				case 'l':
					liNum ++;
					tempString = charString(li);
					temp = new Node(tempString);
					myStack.push(temp);
					break;
				case 's':
					if (s->line[pos + 2] == 'p') {
						tempString = charString(span);
						temp = new Node(tempString);
						myStack.push(temp);
						//first	lauguage
						//second date
						break;
					}
					else {
						tempString = charString(script);
						temp = new Node(tempString);
						myStack.push(temp);
						break;
					}
					break;
				case 'p':
					tempString = charString(p);
					temp = new Node(tempString);
					myStack.push(temp);
					break;
				case 't':
					tempString = charString(textarea);
					temp = new Node(tempString);
					myStack.push(temp);
					break;
				}

				//judge if it is html tag, then push stack
			}
			pos ++;
		}
		else if (s->line[pos] == '>') {
			//if the tag is li or p or textarea, then get info
			if (!myStack.isEmpty()) {
				if (myStack.top->data.line[0] == 't') {
					lyricStart = pos + 1;
				}
				else if (myStack.top->data.line[0] == 'a') {
					if (liNum == 1) {
						singerStart = pos + 1;
					}
					else if (liNum == 3) {
						albumStart = pos + 1;
					}
				}
				else if (myStack.top->data.line[0] == 's' && myStack.top->data.line[1] == 'p') {
					if (liNum == 4) {
						dateStart = pos + 1;
					}
				}
				else if(myStack.top->data.line[0] == 'p') {
					if (s->line[pos + 1] == composerString.line[0] && s->line[pos + 2] == composerString.line[1]) {
						if (s->line[pos + 3] == ':') {
							composerStart = pos + 4;
						}
						else if (s->line[pos + 3] == colonCNString.line[0] && s->line[pos + 4] == colonCNString.line[1]) {
							composerStart = pos + 5;
						}
					}
					else if (s->line[pos + 1] == lyriclistString.line[0] && s->line[pos + 2] == lyriclistString.line[1]) {
						if (s->line[pos + 3] == ':') {
							lyriclistStart = pos + 4;
						}
						else if (s->line[pos + 3] == colonCNString.line[0] && s->line[pos + 4] == colonCNString.line[1]) {
							lyriclistStart = pos + 5;
						}
					}
				}
			}
			
		}
		pos++;
	}
	if (mySong.lyricist.line == NULL) {
		mySong.lyricist = charString(none);
	}
	if (mySong.composer.line == NULL) {
		mySong.composer = charString(none);
	}
	return mySong;
}