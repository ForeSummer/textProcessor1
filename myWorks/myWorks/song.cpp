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
			info = info.concat(s);
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
	//Song mySong = analyzeInfo(&info);
	Song mySong;
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
void analyzeInfo(charString *s) {
	Song mySong;
	Stack myStack;
	myStack.initStack();
	Node *temp = NULL;
	charString tempString;
	string div = "div", h2 = "h2", a = "a", ul = "ul", li = "li", script = "script", span = "span", p = "p", textarea = "textarea";
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
					}
					break;
				case 't':
					if (myStack.top->data.line[0] == 't') {
						myStack.pop();
					}
					break;
				}
				
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
					break;
				case 'a':
					tempString = charString(a);
					temp = new Node(tempString);
					myStack.push(temp);
					break;
				case 'u':
					tempString = charString(ul);
					temp = new Node(tempString);
					myStack.push(temp);
					break;
				case 'l':
					tempString = charString(li);
					temp = new Node(tempString);
					myStack.push(temp);
					break;
				case 's':
					if (s->line[pos + 2] == 'p') {
						tempString = charString(span);
						temp = new Node(tempString);
						myStack.push(temp);
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
			
		}
		else if (s->line[pos] == '>') {
			//if the tag is li or p or textarea, then get info
		}
		pos++;
	}
	return;
}