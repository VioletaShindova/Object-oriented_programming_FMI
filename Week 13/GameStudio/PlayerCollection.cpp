#include "PlayerCollection.h"
#include "Player.h"
#include <iostream>
PlayerCollection::PlayerCollection() : players(nullptr), size(0), capacity(1) {}

PlayerCollection::PlayerCollection(const PlayerCollection& other) : size(other.size), capacity(other.capacity)
{
	copyDynamic(other);
}

PlayerCollection& PlayerCollection::operator=(const PlayerCollection& other)
{
	if (this != &other)
	{
		size = other.size;
		capacity = other.capacity;
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

PlayerCollection::~PlayerCollection() noexcept
{
	freeDynamic();
}

bool PlayerCollection::checkIfFound(const Player* toAddPlayer) const
{
	if(!toAddPlayer)
		throw std::invalid_argument("Invalid player\n");

	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(players[i]->getName(), toAddPlayer->getName()) == 0)
			return true;
	}
	return false;
}

bool PlayerCollection::addPlayer(const Player* toAddPlayer)
{
	if (!toAddPlayer)
		throw std::invalid_argument("Invalid player\n");

	if (!checkIfFound(toAddPlayer))
	{
		if (size + 1 >= capacity)
			resize();

		players[size++] = toAddPlayer->clone();
		return true;
	}
	return false;
}

bool PlayerCollection::removePlayer(const Player* toRemovePlayer)
{
	if (!toRemovePlayer)
		throw std::invalid_argument("Invalid player\n");

	if (!players || size == 0)
		throw std::logic_error("Empty list of players\n");

	if (!checkIfFound(toRemovePlayer))
		return false;

	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(players[i]->getName(), toRemovePlayer->getName()) == 0)
		{
			std::swap(players[i], players[size - 1]);
			delete players[size - 1];
			players[size - 1] = nullptr;
			size--;
			break;

		}
	}
	return true;
}

const Player* PlayerCollection::operator[](int index) const
{
	if (index < 0 || index >= size)
		throw std::invalid_argument("Invalid index\n");

	return players[index];
}

void PlayerCollection::freeDynamic()
{
	for (size_t i = 0; i < size; i++)
	{
		delete players[i];
	}
	delete[] players;
	players = nullptr;
}

void PlayerCollection::copyDynamic(const PlayerCollection& other)
{
	Player** temp = new (std::nothrow) Player * [other.capacity];

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < other.size; i++)
	{
		temp[i] = other.players[i] ? other.players[i]->clone() : nullptr;
	}

	players = temp;
}

void PlayerCollection::resize()
{
	size_t tempCapacity = capacity * 2 + 1;
	Player** temp = new (std::nothrow) Player * [tempCapacity];

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < size; i++)
	{
		temp[i] = players[i];
	}

	delete[] players;
	players = temp;
	capacity = tempCapacity;
}

