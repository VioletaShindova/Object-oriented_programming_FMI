#pragma once


#ifndef __PLAYER_COLLECTION_HEADER_INCLUDED_

#define __PLAYER_COLLECTION_HEADER_INCLUDED_

class Player;

class PlayerCollection
{
public:
	PlayerCollection();
	PlayerCollection(const PlayerCollection& other);
	PlayerCollection& operator=(const PlayerCollection& other);
	~PlayerCollection() noexcept;

	inline Player** getPlayers() const noexcept { return players; }
	inline size_t getCountOfPlayers() const noexcept { return size; }

	bool addPlayer(const Player* toAddPlayer);
	bool removePlayer(const Player* toRemovePlayer);

	const Player* operator[](int index) const;

private:
	bool checkIfFound(const Player* toAddPlayer) const;

	void freeDynamic();
	void copyDynamic(const PlayerCollection& other);
	void resize();

	Player** players;
	size_t size;
	size_t capacity;
};

#endif