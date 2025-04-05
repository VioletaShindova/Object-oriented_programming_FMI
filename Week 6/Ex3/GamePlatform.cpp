#include <iostream>
#include <fstream>
#include "GamePlatform.h"

GamePlatform::GamePlatform(int size) {
	setSize(size);
	setGames();
}

GamePlatform::GamePlatform(const Game* games, int size) {
	setSize(size);
	setGames(games);
}

GamePlatform::GamePlatform(const GamePlatform& other) : size(other.size) {
	copyDynamic(other);
}

GamePlatform& GamePlatform::operator=(const GamePlatform& other) {
	if (this != &other) {
		this->size = other.size;
		freeDynamic();
		copyDynamic(other);
	}

	return *this;
}

GamePlatform::~GamePlatform() {
	freeDynamic();
}

void GamePlatform::setSize(int size) {
	if (!isValidSize(size))
		throw std::out_of_range("Size out of range!");

	this->size = size;
}

void GamePlatform::setGames() {
	this->games = new (std::nothrow) Game[this->size];

	if (!this->games)
		throw std::overflow_error("Not enough memory!");

	for (size_t i = 0; i < this->size; i++)
		this->games[i] = Game();
}

void GamePlatform::setGames(const Game* games) {
	this->games = new (std::nothrow) Game[this->size];

	if (!games || !this->games)
		throw std::overflow_error("Invalid array!");

	for (size_t i = 0; i < this->size; i++)
		this->games[i] = games[i];
}

//optimize, use implementation like vector - resize()
bool GamePlatform::addGame(const Game& game) {
	if (this->size >= capacity)
		return false;

	Game* games = new Game[this->size + 1];
	for (size_t i = 0; i < this->size; i++)
		games[i] = this->games[i];

	games[this->size++] = game;

	freeDynamic();

	this->games = new Game[this->size];

	this->games = games;

	return true;
}

void GamePlatform::printParticularGame(int index) const {
	if (!isValidSize(index))
		throw std::invalid_argument("Invalid index!");

	this->games[index].print();
}

void GamePlatform::printGames() const {
	if (!this->games)
		throw "There are no games in the current list!";

	for (size_t i = 0; i < this->size; i++)
	{
		this->games[i].print();
	}
}

void GamePlatform::getCheapestAndMostExpensiveGame() const {
	size_t cheapest = getIndexOfCheapest();
	size_t mostExpensive = getIndexOfMostExpensive();

	std::cout << "Cheapest game: ";
	this->games[cheapest].print();

	std::cout << "The most expensive game: ";
	this->games[mostExpensive].print();
}

void GamePlatform::printAllFreeGames() const {
	for (size_t i = 0; i < this->size; i++)
	{
		if (this->games[i].isFree())
			this->games[i].print();
	}
}

bool GamePlatform::removeGame(const Game& game) {
	if (!(this->size - 1) || !this->size)
		return false;

	size_t gameOccurances = getOccurancesOfAGame(game);
	Game* newGames = new Game[this->size - gameOccurances];
	for (size_t i = 0; i < this->size; i++)
	{
		if (this->games[i].checkIfAlike(game)) {
			std::swap(this->games[i], this->games[this->size]);
			continue;
		}

		newGames[i] = this->games[i];
	}

	this->size -= gameOccurances;
	this->games = new Game[this->size];
	this->games = newGames;
	return true;
}

bool GamePlatform::writeToBinaryFile(const char* fileName) const {
	if (!fileName)
		return false;

	std::ofstream ofs(fileName, std::ios::binary);

	if (!ofs.is_open())
		return false;

	ofs.write((const char*)&this->size, sizeof(size));

	for (size_t i = 0; i < this->size; i++)
		this->games[i].writeToBinaryFile(ofs);

	ofs.close();
	return true;
}

bool GamePlatform::readFromBinaryFile(const char* fileName) {
	if (!fileName)
		return false;

	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open())
		return false;

	ifs.read((char*)&this->size, sizeof(size));

	freeDynamic();

	Game* games = new Game[this->size];
	this->games = new Game[this->size];

	for (size_t i = 0; i < this->size; i++) {
		//this->games[i].readFromBinaryFile(ifs);
		games[i].readFromBinaryFile(ifs);
		this->games[i] = games[i];
	}
	
	delete[] games;
	ifs.close();
	return true;
}

bool GamePlatform::writeToTextFile(const char* fileName) const {
	if (!fileName)
		return false;

	std::ofstream ofs(fileName);
	if (!ofs.is_open())
		return false;

	ofs << size << ' ';

	for (size_t i = 0; i < this->size; i++)
		this->games[i].writeToTextFile(ofs);

	ofs.close();
	return true;
}

bool GamePlatform::readFromTextFile(const char* fileName) {
	if (!fileName)
		return false;

	std::ifstream ifs(fileName);
	if (!ifs.is_open())
		return false;

	ifs >> this->size;

	freeDynamic();
	this->games = new Game[this->size];

	for (size_t i = 0; i < this->size; i++)
		this->games[i].readFromTextFile(ifs);

	ifs.close();
	return true;
}

bool GamePlatform::isValidSize(int size) const {
	return (0 < size) && (size < MAX_SIZE_GAME);
}

void GamePlatform::copyDynamic(const GamePlatform& other) {
	this->games = new Game[other.size];

	for (size_t i = 0; i < other.size; i++)
		this->games[i] = other.games[i];
}

void GamePlatform::freeDynamic() {
	delete[] this->games;
}

size_t GamePlatform::getIndexOfCheapest() const {
	size_t minIndex = 0;

	for (size_t i = 1; i < this->size; i++) {
		if (this->games[i].getPrice() < this->games[minIndex].getPrice())
			minIndex = i;
	}
	return minIndex;
}

size_t GamePlatform::getIndexOfMostExpensive() const {
	size_t maxIndex = 0;

	for (size_t i = 1; i < this->size; i++) {
		if (this->games[i].getPrice() > this->games[maxIndex].getPrice())
			maxIndex = i;
	}

	return maxIndex;
}