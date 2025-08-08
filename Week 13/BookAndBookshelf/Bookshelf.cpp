#include "Bookshelf.hpp"
#include "Book.hpp"
#include <iostream>

Bookshelf::Shelf::Shelf() : Shelf(nullptr, 0) {}

Bookshelf::Shelf::Shelf(const Book** books, int countBooks) : books(nullptr), countBooks(0)
{
	setBooks(books, countBooks);
}

Bookshelf::Shelf::Shelf(const Shelf& other) : countBooks(other.countBooks), pagesSum(other.pagesSum)
{
	copyDynamic(other);
}

Bookshelf::Shelf& Bookshelf::Shelf::operator=(const Shelf& other)
{
	if(this != &other)
	{
		countBooks = other.countBooks;
		pagesSum = other.pagesSum;
		freeDynamic();
		copyDynamic(other);
	}

	return *this;
}

Bookshelf::Shelf::~Shelf() noexcept
{
	freeDynamic();
}

bool Bookshelf::Shelf::addBookToShelf(const Book* newBook)
{
	if (!newBook)
		return false;

	Book** temp = new (std::nothrow) Book * [countBooks + 1];

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < countBooks; i++)
	{
		temp[i] = books[i];
	}

	temp[countBooks] = const_cast<Book*>(newBook);

	delete[] books;
	books = temp;
	countBooks++;
	pagesSum += newBook->getPages();

	return true;
}

bool Bookshelf::Shelf::removeBookToShelf(const Book* bookToRemove)
{
	if (!bookToRemove || countBooks == 0)
		return false;

	for (size_t i = 0; i < countBooks; i++)
	{
		if (areEqual(books[i], bookToRemove)) {
			std::swap(books[i], books[countBooks - 1]);
			delete books[countBooks - 1];
			countBooks--;
			pagesSum -= bookToRemove->getPages();

			if (countBooks > 0)
			{
				Book** temp = new (std::nothrow) Book * [countBooks];
				if (!temp)
					throw std::bad_alloc();

				for (size_t j = 0; j < countBooks; j++)
					temp[j] = books[j];

				delete[] books;
				books = temp;
			}
			else {
				delete[] books;
				books = nullptr;
			}

			return true; 
		}
	}

	return false; //book was not found
}

void Bookshelf::Shelf::setBooks(const Book** books, int countBooks)
{
	if (!books || countBooks < 0)
		throw std::invalid_argument("Invalid array\n");

	Book** temp = new (std::nothrow) Book * [countBooks];

	if (!temp)
		throw std::bad_alloc();

	pagesSum = 0;
	for (size_t i = 0; i < countBooks; i++)
	{
		(temp[i]) = const_cast<Book*>(books[i]);

		pagesSum += temp[i]->getPages();
	}

	delete[] this->books;
	this->books = temp;
	this->countBooks = countBooks;
}

void Bookshelf::Shelf::copyDynamic(const Shelf& other)
{
	Book** tempBooks = new (std::nothrow) Book * [other.countBooks];

	if (!tempBooks)
		throw std::bad_alloc();

	for (size_t i = 0; i < other.countBooks; i++)
	{
		if (!other.books[i])
			throw std::invalid_argument("Null book in source shelf\n");

		//deep copy is better than shallow copy - tempBooks[i] = other.books[i]
		tempBooks[i] = new (std::nothrow) Book(*other.books[i]); 

		if (!tempBooks[i]) {
			for (size_t j = 0; j  < i; j ++)
			{
				delete tempBooks[j];
			}
			delete[] tempBooks;
			throw std::bad_alloc();
		}
	}

	delete[] books;
	books = tempBooks;
}

void Bookshelf::Shelf::freeDynamic()
{
	for (size_t i = 0; i < this->countBooks; i++)
	{
		delete this->books[i];
	}

	delete[] this->books;
	this->books = nullptr;
}

Bookshelf::Bookshelf(int countShelves) 
	: shelves(nullptr), countShelves(0), capacity(this->countShelves + 1), maxPagesSum(2000)
{
	setShelves(countShelves);
}

Bookshelf::Bookshelf(int countShelves, int maxPagesSum) 
	: shelves(nullptr), countShelves(0), capacity(this->countShelves + 1), maxPagesSum(2000)
{
	setMaxPagesSum(maxPagesSum);
	setShelves(countShelves);
}

Bookshelf::Bookshelf(const Shelf* shelves, int countShelves, int maxPagesSum) 
	: shelves(nullptr), countShelves(0), capacity(this->countShelves + 1), maxPagesSum(2000)
{
	setMaxPagesSum(maxPagesSum);
	setShelves(shelves, countShelves);
}

Bookshelf::~Bookshelf() noexcept
{
	freeDynamic();
}

bool Bookshelf::addBook(const Book* newBook)
{
	if (!newBook)
		return false;

	if (findBook(newBook)) 
		throw std::invalid_argument("Can't add the same book more than once\n");
	
	for (size_t i = 0; i < countShelves; i++)
	{
		unsigned pagesSum = shelves[i].getPagesSum();

		if (pagesSum + newBook->getPages() > getMaxPagesSum())
			continue;
		else 
			return shelves[i].addBookToShelf(newBook);
	}

	return true;
}

bool Bookshelf::writeToStream(std::ostream& os) const
{
	if(!os.good())
		return false;

	for (size_t i = 0; i < countShelves; i++) {

		unsigned countBooksOfEachShelf = shelves[i].getCountBooks();
		Book** booksOfEachShelf = shelves[i].getBooks();

		for (size_t j = 0; j < countBooksOfEachShelf; j++) {
			booksOfEachShelf[j]->writeToStream(os);
		}
	}

	return true;
}

bool Bookshelf::findBook(const Book* bookToFind) const
{
	if (!bookToFind)
		return false;

	for (size_t i = 0; i < countShelves; i++) {

		unsigned countBooksOfEachShelf = shelves[i].getCountBooks();
		Book** booksOfEachShelf = shelves[i].getBooks();

		for (size_t j = 0; j < countBooksOfEachShelf; j++) {
			if (areEqual(booksOfEachShelf[j], bookToFind))
				return true;
		}
	}
	return false;
}

bool Bookshelf::removeBook(const Book* bookToRemove)
{
	if(!bookToRemove)
		return false;

	if (!findBook(bookToRemove))
		throw std::logic_error("Can't remove a book that doesn't exist\n");
	
	for (size_t i = 0; i < countShelves; i++)
	{
		if (shelves[i].removeBookToShelf(bookToRemove))
			return true;
	}

	return false;
}

void Bookshelf::setShelves(int countShelves)
{
	if (countShelves < 0)
		throw std::invalid_argument("Shelves count must be a positive number\n");
	
	Shelf* tempShelves = new (std::nothrow) Shelf[(countShelves * 2) + 1];

	if (!tempShelves)
		throw std::bad_alloc();

	for (size_t i = 0; i < countShelves; i++)
	{
		tempShelves[i] = Shelf();
	}

	this->countShelves = countShelves;
	this->capacity = (countShelves * 2) + 1;
	delete[] shelves;
	shelves = tempShelves;
}

void Bookshelf::setShelves(const Shelf* shelves, int countShelves)
{
	if (countShelves < 0)
		throw std::invalid_argument("Shelves count must be a positive number\n");

	Shelf* tempShelves = new (std::nothrow) Shelf[(countShelves * 2) + 1];

	if (!tempShelves)
		throw std::bad_alloc();

	for (size_t i = 0; i < countShelves; i++)
	{
		tempShelves[i] = shelves[i];
	}

	this->countShelves = countShelves;
	this->capacity = (countShelves * 2) + 1;
	delete[] this->shelves;
	this->shelves = tempShelves;
}

void Bookshelf::resize()
{
	Shelf* tempShelves = new (std::nothrow) Shelf[(capacity * 2) + 1];

	if (!tempShelves)
		throw std::bad_alloc();

	for (size_t i = 0; i < countShelves; i++)
	{
		tempShelves[i] = shelves[i];
	}

	countShelves = capacity;
	capacity = (capacity * 2) + 1;
	delete[] shelves;
	shelves = tempShelves;
}

void Bookshelf::resizeMaxPagesCapacityOfShelves(unsigned newMaxPagesSum)
{

}

void Bookshelf::copyDynamic(const Bookshelf& other)
{
	Shelf* tempShelves = new (std::nothrow) Shelf[other.capacity];

	if (!tempShelves)
		throw std::bad_alloc();

	for (size_t i = 0; i < other.countShelves; i++)
	{
		tempShelves[i] = other.shelves[i];
	}

	delete[] shelves;
	shelves = tempShelves;
}

void Bookshelf::freeDynamic()
{
	delete[] shelves;
	shelves = nullptr;
}

void Bookshelf::setMaxPagesSum(int maxPagesSum)
{
	if (maxPagesSum < 0)
		throw std::invalid_argument("Max capacity of pages must be a positive number\n");

	resizeMaxPagesCapacityOfShelves(maxPagesSum);

	this->maxPagesSum = maxPagesSum;
}
