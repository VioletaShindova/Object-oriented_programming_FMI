#pragma once
#include "Game.h"

constexpr size_t MAX_SIZE_GAME = 64;

class GamePlatform
{
public:
	GamePlatform() = default;

	explicit GamePlatform(int size);

	GamePlatform(const Game* games, int size);

	GamePlatform(const GamePlatform& other);

	GamePlatform& operator=(const GamePlatform& other);

	~GamePlatform();

	void setSize(int size);

	void setGames();

	void setGames(const Game* games);

	bool addGame(const Game& game);

	void printParticularGame(int index) const;

	void printGames() const;

	void getCheapestAndMostExpensiveGame() const;

	void printAllFreeGames() const;

	bool removeGame(const Game& game);

	bool writeToBinaryFile(const char* fileName) const;

	bool readFromBinaryFile(const char* fileName);

	bool writeToTextFile(const char* fileName) const;

	bool readFromTextFile(const char* fileName);

private:
	bool isValidSize(int size) const;

	void copyDynamic(const GamePlatform& other);

	void freeDynamic();

	size_t getIndexOfCheapest() const;

	size_t getIndexOfMostExpensive() const;

	size_t getOccurrencesOfAGame(const Game& game) const;

	Game* games = nullptr;
	size_t size = 0;
	size_t capacity = MAX_SIZE_GAME - size;
};

