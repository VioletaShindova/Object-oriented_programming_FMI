// Ex5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Song.h"
using std::cout;
using std::endl;
using std::cin;
/*
Създайте структура, която представлява песен, която съдържа следните характеристики:

заглавие (до 100 символа)
изпълнител (до 100 символа)
жанр (може да бъде Rock, Pop, Thrash Metal, K-pop, Chalga)
рейтинг (дробно число от 0 до 5)
брой слушания (цяло число)

Създайте структура Playlist, която се описва с най-много 64 песни. Реализирайте следните функции:

добавяне на песен в колекцията (ако капацитетът е запълнен, принтирайте подходящо съобщение)
връщане на указател към песен по подаден предикат, приемащ като аргумент 1 песен
сортиране на песните по подаден предикат, приемащ като аргументи 2 песни
*/

Song searchSong;

int main()
{
	Playlist playlist;
	Song song;

	readSong(song);
	addSongInPLaylist(playlist, song);

	readSong(song);
	addSongInPLaylist(playlist, song);

	cout << "Search song: " << endl;
	readSong(searchSong);

	const Song* ptrSong = getSong(playlist, [](const Song& song)
		{
			return strcmp(song.singer, searchSong.singer) == 0;	
		});

	if (ptrSong) {
		cout << ptrSong->title << std::endl;
		//cout << ptrSong->genre << std::endl;
	}
	else {
		cout << "Song not found!" << std::endl;
	}

	sortSongsByViews(playlist, [](const Song& firstSong, const Song& secondSong)
		{
			return firstSong.views > secondSong.views;
		});

	printSongNames(playlist);
}

