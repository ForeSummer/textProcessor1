#include <iostream>
#include <fstream>
using namespace std;
#include "song.h"

int main() {
	string filePath = "0001.html";
	ifstream inFs(filePath, ios::in);
	string match1 = "song_info_area", match2 = "music_list_area";
	charString matchString1 = charString(match1), matchString2 = charString(match2);
	charString s, info;
	string temp;
	while (!inFs.eof())
	{
		getline(inFs,temp);
		s = charString(temp);
		if(getPart(s, matchString1))	{
			break;
		}
	}
	while (!inFs.eof())
	{
		getline(inFs,temp);
		cout << temp<<endl;
		s = charString(temp);
		if(getPart(s, matchString2))	{
			break;
		}
		info.concat(s);
	}
	return 0;
}