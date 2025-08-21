#pragma once

#ifndef __GAME_HEADER_INCLUDED_

#define __GAME_HEADER_INCLUDED_

#include <iostream>

namespace GlobalConstants {
	static constexpr size_t MIN_BORDER = 1;
	static constexpr size_t MAX_BORDER = 100;
}

class Artifact;
class Teleport;
class Player;

enum class TypeArtifact {
	INVALID,
	TELEPORT,
	PRESENT,
	MONSTER,
	COMBINED_SUBJECTS,
	COUNT
};

class Game
{
public:
	friend class Teleport;

	struct WrapperArtifacts {
	public:
		WrapperArtifacts();
		WrapperArtifacts(const WrapperArtifacts& other);
		WrapperArtifacts& operator=(const WrapperArtifacts& other);
		~WrapperArtifacts() noexcept;

		inline Artifact** getArtifacts() noexcept { return artifacts; }
		inline size_t getSizeOfArtifacts() const noexcept { return sizeOfArtifacts; }

		void setArtifact(int position, const Artifact& artifact);

	private:
		void setArtifacts();
		void freeDynamic();
		void copyDynamic(const WrapperArtifacts& other);

		Artifact** artifacts;
		size_t sizeOfArtifacts;
	};

	Game();
	explicit Game(int capacity);
	Game(int capacity, int countOfArtifacts);
	Game(const Game& other);
	Game& operator=(const Game& other);
	~Game() noexcept;
	
	inline const WrapperArtifacts* getEachLineOfArtifact() const noexcept { return eachLineOfArtifact; }
	inline size_t getSize() const noexcept { return size; }
	inline unsigned getCountOfArtifacts() const noexcept { return countOfArtifacts; }

	static void run(Game& game);

private:
	void interact(Artifact* artifact, Player& player);

	static unsigned incrementCurrentIndexOfLineOfArtifact();
	void rollDice(Player& player);

	void setCapacity(int capacity);
	void setArtifacts(int countOfArtifacts); //sets all the elements on the map

	bool isPositionInBorders(int newPosition) const;
	void freeDynamic();
	void copyDynamic(const Game& other);
	void resize();

	WrapperArtifacts* eachLineOfArtifact;
	size_t size;
	size_t capacity;

	unsigned countOfArtifacts;

	static unsigned currentIndexOfLineOfArtifact;
};

#endif