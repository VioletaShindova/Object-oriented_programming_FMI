	#include <iostream>
#include "Song.h"

/*
Създайте структура, която представлява песен, която съдържа следните характеристики:

заглавие (до 100 символа)
изпълнител (до 100 символа)
жанр (може да бъде Rock, Pop, Thrash Metal, K-pop, Chalga)
рейтинг (дробно число от 0 до 5)
брой слушания (цяло число)
*/

void readSong(Song& song)
{
	std::cout << "Title: ";
	std::cin.ignore();
	std::cin.getline(song.title, MAXSTRLENNAME);

	std::cout << "Singer: ";
	std::cin.ignore();
	std::cin.getline(song.singer, MAXSTRLENNAME);

	int number;
	std::cout << "Genre: ";
	std::cin >> number;
	song.genre = (Genre)number;

	std::cout << "Rating: ";
	std::cin >> song.rating;

	std::cout << "Views: ";
	std::cin >> song.views;
}

void addSongInPLaylist(Playlist& playlist, const Song& song)
{
	//check capacity
	if (playlist.size >= MAXSONGS)
	{
		std::cout << "Can't add, full of capacity!";
		return;
	}
	
	playlist.songs[playlist.size] = song;
	playlist.size++;

	return;
}

const Song* getSong(const Playlist& playlist, bool (*predHasSong)(const Song& song)) 
{
	const Song* ptrForSong = nullptr;
	for (size_t i = 0; i < playlist.size; i++)
	{
		if (predHasSong(playlist.songs[i]))
		{
			
			ptrForSong = &playlist.songs[i];
			break;
		}
	}

	return ptrForSong;
}

void sortSongsByViews(Playlist& playlist, bool (*isLess)(const Song& first, const Song& second))
{
	for (size_t i = 0; i < playlist.size - 1; i++)
	{
		size_t minElementIndex = i;
		for (size_t j = i + 1; j < playlist.size; j++)
		{
			if (isLess(playlist.songs[j], playlist.songs[minElementIndex]))
			{
				minElementIndex = j;
			}
		}

		if (minElementIndex != i)
		{
			std::swap(playlist.songs[i], playlist.songs[minElementIndex]);
		}
	}
}

void printSongNames(const Playlist& playlist)
{
	for (size_t i = 0; i < playlist.size; i++)
	{
		std::cout << playlist.songs[i].title << std::endl;
	}
}