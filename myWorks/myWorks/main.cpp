#include <iostream>
#include <fstream>
using namespace std;
#include "song.h"
#include "stack.h"

int main() {
	string filePath = "0001.html";
	ifstream inFs(filePath, ios::in);
	string match1 = "song_info_area", match2 = "music_list_area";
	charString matchString1 = charString(match1), matchString2 = charString(match2);
	charString s, info ;
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
		//cout << temp<<endl;
		s = charString(temp);
		//cout << s.toString()<<endl;
		//cout << s.length<<endl;
		if(getPart(s, matchString2))	{
			
			break;
		}
		info = info.concat(s);
		
		//cout << info.toString()<<endl;
	}
	//cout << info.toString()<<endl;
	//Song mySong = analyzeInfo(&info);
	analyzeInfo(&info);
	return 0;
}