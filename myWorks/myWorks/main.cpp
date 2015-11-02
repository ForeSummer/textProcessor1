#include <iostream>
#include <fstream>
using namespace std;
#include "song.h"
#include "stack.h"

int main() {
	string filePath = "0010.html";
	Song mySong = extractMusicInfoFromPage(filePath);
	mySong.printSongInfo("out.txt");
	return 0;
}