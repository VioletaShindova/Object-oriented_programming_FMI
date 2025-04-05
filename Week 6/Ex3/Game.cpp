#include "Game.h"
#include <iostream>
#pragma warning (disable: 4996)

Game::Game(const char* title) {
	setTitle(title);
}

Game::Game(const char* title, float price) {
	setTitle(title);
	setPrice(price);
}

Game::Game(const char* title, float price, int isAvailable) {
	setTitle(title);
	setPrice(price);
	setStatus(isAvailable);
}

void Game::setTitle(const char* title) {
	if (!isValidTitle(title))
		throw std::invalid_argument("Invalid title!");

	strcpy(this->title, title);
}

void Game::setPrice(float price) {
	if (!isValidPrice(price))
		throw std::invalid_argument("Invalid price!");

	this->price = price;
}

void Game::setStatus(int isAvailable) {
	if (!isValidStatus(isAvailable))
		throw std::invalid_argument("Invalid status!");

	this->isAvailable = isAvailable;
}

const char* Game::getTitle() const {
	return this->title;
	/*const char* tempTitle = new char[strlen(this->title) + 1];
	return tempTitle;*/
}

const float Game::getPrice() const {
	return this->price;
}

const bool Game::getStatus() const {
	return this->isAvailable;
}

bool Game::isFree() const {
	return this->isAvailable && !this->price;
}

void Game::print() const {
	std::cout << "Title: " << this->title;
	std::cout << " Price: " << this->price << " Status: " << this->isAvailable << std::endl;
}

void Game::writeToBinaryFile(std::ofstream& ofs) const {

	size_t currSizeOfTitle = strlen(title);
	ofs.write((const char*)&currSizeOfTitle, sizeof(currSizeOfTitle));

	ofs.write((const char*)title, currSizeOfTitle);

	ofs.write((const char*)&price, sizeof(price));

	ofs.write((const char*)&isAvailable, sizeof(isAvailable));
}

void Game::readFromBinaryFile(std::ifstream& ifs) {
	size_t currSizeOfTitle = 0;
	ifs.read((char*)&currSizeOfTitle, sizeof(currSizeOfTitle));

	if (currSizeOfTitle >= MAX_TITLE_LEN)
		currSizeOfTitle = MAX_TITLE_LEN - 1;

	ifs.read((char*)title, currSizeOfTitle);
	this->title[currSizeOfTitle] = '\0';

	ifs.read((char*)&price, sizeof(price));

	ifs.read((char*)&isAvailable, sizeof(isAvailable));
}

void Game::writeToTextFile(std::ofstream& ofs) const {
	ofs << title << '\n' << price << '\n' << isAvailable;
}

void Game::readFromTextFile(std::ifstream& ifs) {
	ifs.getline(title, MAX_TITLE_LEN, '\n');
	ifs >> price >> isAvailable;
}

bool Game::isValidTitle(const char* title) const {
	return title && 0 < strlen(title) && strlen(title) <= MAX_TITLE_LEN;
}

bool Game::isValidPrice(float price) const {
	return 0 <= price;
}

bool Game::isValidStatus(int isAvailable) const {
	return isAvailable == 0 || isAvailable == 1;
}