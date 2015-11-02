#ifndef SONG_H
#define SONG_H

#include "charString.h"

class Song
{
public :
	charString title;
	charString singer;
	charString album;
	charString publicDate;
	charString lyricist;
	charString composer;
	charString lyrics;
public:
	 Song();
	 Song(Song &s);
	 ~Song();
	 void printSongInfo(string outputPath);
	 Song& operator = (const Song& s);
};


extern Song getSongInfo(string filePath);
extern bool getPart(charString s, charString match);
extern void analyzeInfo(charString* s);

#endif