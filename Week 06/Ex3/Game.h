#pragma once
#include <fstream>

constexpr size_t MAX_TITLE_LEN = 64;

class Game
{
public:
	Game() = default;

	explicit Game(const char* title);

	Game(const char* title, float price);

	Game(const char* title, float price, int isAvailable);

	void setTitle(const char* title);

	void setPrice(float price);

	void setStatus(int isAvailable);

	const char* getTitle() const;

	const float getPrice() const;

	const bool getStatus() const;

	bool isFree() const;

	void print() const;

	void writeToBinaryFile(std::ofstream& ofs) const;

	void readFromBinaryFile(std::ifstream& ifs);

	void writeToTextFile(std::ofstream& ofs) const;

	void readFromTextFile(std::ifstream& ifs);

	bool checkIfAlike(const Game& other) const;

private:
	bool isValidTitle(const char* title) const;

	bool isValidPrice(float price) const;

	bool isValidStatus(int isAvailable) const;

	char title[MAX_TITLE_LEN] = "";
	float price = 0;
	bool isAvailable = true;
};

