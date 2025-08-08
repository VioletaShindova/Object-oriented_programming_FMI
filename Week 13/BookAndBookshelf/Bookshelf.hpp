#pragma once

#ifndef __BOOKSHELF_HEADER_INCLUDED_
#define __BOOKSHELF_HEADER_INCLUDED_

#include <iostream>

class Book;

class Bookshelf
{
public:
	struct Shelf {
	public:
		Shelf();
		Shelf(const Book** books, int countBooks);
		Shelf(const Shelf& other);
		Shelf& operator=(const Shelf& other);
		~Shelf() noexcept;

		inline Book** getBooks() noexcept { return books; }
		inline size_t getCountBooks() const noexcept { return countBooks; }
		inline unsigned getPagesSum() const noexcept { return pagesSum; }

		bool addBookToShelf(const Book* newBook);
		bool removeBookToShelf(const Book* bookToRemove);
		void setBooks(const Book** books, int countBooks);

	private:
		void copyDynamic(const Shelf& other);
		void freeDynamic();

		Book** books;
		size_t countBooks;

		unsigned pagesSum;
	};

	Bookshelf() = delete;

	explicit Bookshelf(int countShelves);

	Bookshelf(int countShelves, int maxPagesSum);

	Bookshelf(const Shelf* shelves, int countShelves, int maxPagesSum = 2000);

	Bookshelf(const Bookshelf& other) = delete;
	Bookshelf& operator=(const Bookshelf& other) = delete;

	~Bookshelf() noexcept;

	bool addBook(const Book* newBook); //една книга може да бъде поставена в не повече от една библиотека.

	bool writeToStream(std::ostream& os) const;

	bool findBook(const Book* bookToFind) const;

	bool removeBook(const Book* bookToRemove);

	void setMaxPagesSum(int maxPagesSum);

	inline const Shelf* getShelves() const noexcept { return shelves; }
	inline size_t getCountShelves() const noexcept { return countShelves; }
	inline unsigned getMaxPagesSum() const noexcept { return maxPagesSum; }

private:
	//overloading
	void setShelves(int countShelves);
	void setShelves(const Shelf* shelves, int countShelves);

	void resize();

	void resizeMaxPagesCapacityOfShelves(unsigned newMaxPagesSum);

	void copyDynamic(const Bookshelf& other);
	void freeDynamic();

	Shelf* shelves = nullptr;
	size_t countShelves;
	size_t capacity;

	unsigned maxPagesSum; //променя. На всеки рафт могат да се поместят толкова книги, че
								//общият им брой страници не трябва да надвишава предварително определен максимален брой.
};

#endif