#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Item
{
public:
	Item();
	Item(const std::string& title, const std::string& publisher,
		const std::string& genre, const std::string& description,
		int yearPublished, int rating);

	virtual ~Item() noexcept = default;

	virtual Item* clone() const = 0;

	void setTitle(const std::string& title);
	void setPublisher(const std::string& publisher);
	void setGenre(const std::string& genre);
	void setDescription(const std::string& description);

	void setYearPublished(int yearPublished);
	void setRating(int rating);
	
	const std::string& getTitle() const noexcept;
	const std::string& getPublisher() const noexcept;
	const std::string& getGenre() const noexcept;
	const std::string& getDescription() const noexcept;

	unsigned getYearPublished() const noexcept;
	unsigned getRating() const noexcept;

	unsigned getID() const noexcept;

	virtual void print() const = 0;

	virtual void saveToFile(const std::string& fileName) const = 0;

	virtual void saveAllToFile(std::ofstream& ofs) const = 0; //meaning flush all info when the dtor of library is called

	static void writeIDToTextFile(const char* fileName);
	static void readIDFromTextFile(const char* fileName);

	virtual std::string getType() const = 0;

protected:

private:
	std::string title;
	std::string publisher;
	std::string genre;
	std::string description;
	unsigned yearPublished; 
	unsigned rating;
	unsigned id = 1;

	static unsigned currentID;
};

