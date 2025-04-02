#include "Message.h"
#include <iostream>
#include <fstream>

#define MIN(a, b) (a < b) ? a : b 

size_t getFileSize(std::ifstream& ifs) {
	int curr = ifs.tellg();

	ifs.seekg(0, std::ios::end);

	size_t result = ifs.tellg();

	ifs.seekg(curr, std::ios::beg);

	return result;
}

Message::Message(int size) {
	if (!setSize(size))
		throw "Invalid size!";

	this->messageContent = new unsigned[size];
}

Message::Message(int size, int key) {
	if (!setSize(size))
		throw "Invalid size!";

	if (!setKey(key))
		throw "Invalid key!";

	this->messageContent = new unsigned[size];
}

Message::Message(unsigned* messageContent, size_t size, unsigned key) {
	this->messageContent = new (std::nothrow) unsigned[size];
	if (!this->messageContent || !messageContent)
		throw "Invalid message or size!";

	for (size_t i = 0; i < size; i++)
	{
		this->messageContent[i] = messageContent[i];
	}
	this->key = key;
	this->size = size;
}

Message::Message(const Message& other) : size(other.size), key(other.key) {
	copyDynamic(other);
}

Message& Message::operator=(const Message& other) {
	if (this != &other) {
		freeDynamic();
		copyDynamic(other);
		this->size = other.size;
		this->key = other.key;
	}
	return *this;
}

Message::~Message() {
	freeDynamic();
}

bool Message::setSize(int size) {
	if (!isValidSize(size))
		return false;

	this->size = size;
	return true;
}

bool Message::setKey(int key) {
	if (!isValidKey(key))
		return false;

	this->key = key;
	return true;
}

bool Message::writeToBinaryFile(const char* fileName) const {
	if (!fileName)
		return false;

	std::ofstream ofs(fileName, std::ios::binary);

	if (!ofs.is_open())
		return false;

	ofs.write((const char*)this->messageContent, sizeof(unsigned) * size);

	ofs.close();
	return true;
}

bool Message::writeToBinaryFileUsingKey(const char* fileName) {
	if (!fileName || !this->messageContent)
		return false;

	std::ofstream ofs(fileName, std::ios::binary);

	if (!ofs.is_open())
		return false;

	unsigned* temp = new unsigned[this->size];

	for (size_t i = 0; i < this->size; i++)
		temp[i] = this->messageContent[i];

	encrypt(temp);

	ofs.write((const char*)temp, sizeof(unsigned) * size);

	ofs.close();
	delete[] temp;
	return true;
}

bool Message::readFromBinaryFile(const char* fileName) {
	if (!fileName)
		return false;

	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open())
		return false;

	ifs.read((char*)this->messageContent, MIN(getFileSize(ifs), sizeof(unsigned) * size));

	ifs.close();
	return true;
}

void Message::print() const {
	for (size_t i = 0; i < this->size; i++)
		std::cout << this->messageContent[i] << ' ';
}

bool Message::isValidSize(int size) const {
	return 0 < size;
}

bool Message::isValidKey(int key) const {
	return (0 <= key) && (key <= 255);
}

void Message::copyDynamic(const Message& other) {
	this->messageContent = new unsigned[other.size];
	for (size_t i = 0; i < other.size; i++)
	{
		this->messageContent[i] = other.messageContent[i];
	}
}

void Message::freeDynamic() {
	delete[] messageContent;
}

void Message::encrypt(unsigned* message) {
	for (size_t i = 0; i < this->size; i++)
		message[i] += this->key;
}