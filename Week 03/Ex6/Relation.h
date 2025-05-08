#pragma once
#include "Pair.h"

struct Relation {
public:
	Relation() = default;

	explicit Relation(size_t size);

	Relation(Pair* pair, size_t size);

	~Relation();

	bool setSize(size_t size);

	bool setPair(Pair* pair, size_t size);

	size_t getSize() const;

	const size_t getConstSize() const;

	Pair* getPair() const;

	const Pair* getConstPair() const;

	bool readRelationFromFile(const char* fileName);

	bool addPairToRelation(const Pair& pair);

	bool writeRelationToFile(const char* fileName) const;

	void printRelations() const;
		
private:
	bool isValidSize(size_t size) const;

	bool hasCapacity() const;

	Pair* pair = nullptr;
	size_t size = 0;
	size_t capacity = 25 - this->size;
};