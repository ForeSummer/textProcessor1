#include <iostream>
#include <fstream>
using namespace std;
#include "song.h"
#include "stack.h"

int main() {
	string filePath = "0001.html";
	Song mySong = getSongInfo(filePath);
	mySong.printSongInfo("out.txt");
	return 0;
}