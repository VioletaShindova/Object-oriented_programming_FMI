#include "Library.h"

Library::Library() : currentLoggedUser(nullptr)
{
	Item::readIDFromTextFile("lastID.txt");
	deserialize();

	if (users.empty()) 
	{
		users.push_back(new Administrator("admin", "i<3c++", "admin@library.com"));
	}
}

Library::Library(const std::vector<User*>& users, const std::vector<Item*>& items)
{
	Item::readIDFromTextFile("lastID.txt");
	setUsers(users);
	setItems(items);
}

Library::Library(const Library& other)
{
	copyDynamic(other);
}

Library& Library::operator=(const Library& other)
{
	if (this != &other) 
	{
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

Library::~Library()
{
	serialize();
	Item::writeIDToTextFile("lastID.txt");
	freeDynamic();
}

void Library::setUsers(const std::vector<User*>& users)
{
	if (users.empty())
		throw std::invalid_argument("Empty user list is not allowed!");

	for (User* user : users) {
		if (user) {
			this->users.push_back(user->clone());
		}
	}
}

void Library::setItems(const std::vector<Item*>& items)
{
	if (items.empty())
		throw std::invalid_argument("Empty item list is not allowed!");

	for (Item* item : items) {
		if (item) {
			this->items.push_back(item->clone());
		}
	}
}

const std::vector<User*>& Library::getUsers() const noexcept
{
	return users;
}

const std::vector<Item*>& Library::getItems() const noexcept
{
	return items;
}

const User* Library::getCurrentLoggedUser() const noexcept
{
	return currentLoggedUser;
}

bool Library::isSomeoneLogged() const
{
	return currentLoggedUser != nullptr;
}

void Library::run()
{
	std::string command;
	while (true)
	{
		std::cout << "> ";
		command = readLine(std::cin);

		Command* currCmd = CommandFactory::createCommand(command, *this);

		if (!currCmd) {
			std::cout << "Unknown command. Type 'help' to see all commands\n";
			continue;
		}

		/*if (currCmd->isExcutable()) { //must be added

		}*/
		try {
			currCmd->execute();
		}
		catch (std::string& message) {
			std::cout << message;
			delete currCmd;
			break;
		}
		catch (std::exception& e) {
			std::cout << e.what();
		}

		delete currCmd;
	}
}

void Library::login(const User* user)
{
	currentLoggedUser = user->clone();
	user->setLastLogInDate();
	std::cout << "Welcome, " << user->getUsername() << std::endl;
}

void Library::logout()
{
	if (!currentLoggedUser)
		return;

	std::cout << currentLoggedUser->getUsername() << " logged out" << std::endl;
	currentLoggedUser = nullptr;
}

void Library::addUser(User* newUser)
{
	if (!newUser)
		throw std::invalid_argument("Invalid user\n");

	users.push_back(newUser);
}

void Library::addItem(Item* newItem)
{
	if (!newItem)
		throw std::invalid_argument("Invalid item\n");

	items.push_back(newItem);
}

static void selfPrint(std::ifstream& ifs)
{
	int currPosition = ifs.tellg();

	size_t pageCounter = 1;
	size_t lineCounter = 1;
	char symbol;
	std::cout << "Page: " << pageCounter << std::endl;
	while (ifs.get(symbol))
	{
		if (lineCounter == 20) {

			std::cout << std::endl << "Do you want to show the next page? Type 'yes' or 'no'" << std::endl;

			std::string result;
			std::cin >> result;

			if (result == "yes")
			{
				++pageCounter;
				std::cout << std::endl << "Page: " << pageCounter << std::endl;
				lineCounter = 1;
			}
			else if (result == "no")
				break;
		}
		if (symbol == '\n')
			lineCounter++;

		std::cout << symbol;
	}

	ifs.clear();
	ifs.seekg(currPosition, std::ios::beg);
}

void Library::print(const std::string& fileName) const
{
	if (fileName.empty())
		throw std::invalid_argument("Invalid file name\n");

	std::ifstream ifs(fileName);

	if (!ifs.is_open())
		throw std::runtime_error("Can't open file\n");

	selfPrint(ifs);

	ifs.close();
	/*size_t usersLen = users.size();
	for (size_t i = 0; i < usersLen; i++)
	{
		users[i]->print(std::cout);
		std::cout << std::endl;
	}*/
}

static Item* getInfoOfItemWithISBN(std::ifstream& ifs, const std::string& isbnToFind)
{
	std::streampos currPosition = ifs.tellg();

	std::string line;
	while (std::getline(ifs, line)) {
		std::vector<std::string> fields = split(line, ',');

		if (fields.size() != 10) //1o fields to fill
			continue;

		std::string id = fields[0];
		std::string author = fields[1];
		std::string title = fields[2];
		std::string publisher = fields[3];
		std::string genre = fields[4];
		std::string description = fields[5];
		int year = parseToInt(fields[6]);
		int rating = parseToInt(fields[7]);
		std::string keywordRaw = fields[8];
		std::string isbnInFile = fields[9];

		if (isbnInFile == isbnToFind) {
			std::vector<std::string> keyWords = split(keywordRaw, ';'); //we accpect the the key words are separated with ';'

			ifs.clear();
			ifs.seekg(currPosition, std::ios::beg);
			return new Book(title, publisher, genre, description, year, rating, author, keyWords, isbnInFile.c_str()); //we need const char* and c_str returns const char*
		}
	}

	ifs.clear();
	ifs.seekg(currPosition, std::ios::beg);
	return nullptr;
}

static Item* getInfoOfItemWithISSN(std::ifstream& ifs, const std::string& issnToFind)
{
	std::streampos currPosition = ifs.tellg(); 

	std::string line;
	while (std::getline(ifs, line)) {
		std::vector<std::string> fields = split(line, ',');

		if (fields.size() != 11) 
			continue;

		std::string id = fields[0];
		std::string title = fields[1];
		std::string publisher = fields[2];
		std::string genre = fields[3];
		std::string description = fields[4];
		int year = parseToInt(fields[5]);
		int month = parseToInt(fields[6]);
		int count = parseToInt(fields[7]);
		int rating = parseToInt(fields[8]);
		std::string issnInFile = fields[9];

		if (issnInFile != issnToFind)
			continue;

		std::vector<Periodical::Contents> contents;
		std::vector<std::string> rawContents = split(fields[10], ';');

		for (const std::string& entry : rawContents) {
			std::vector<std::string> parts = split(entry, '|');
			if (parts.size() != 3) 
				continue;

			std::vector<std::string> kws = split(parts[2], '&'); //key words for periodical are separated with &
			Periodical::Contents article(parts[0], parts[1], kws);
			contents.push_back(article);
		}

		ifs.clear();
		ifs.seekg(currPosition, std::ios::beg);

		return new Periodical(title, publisher, genre, description, year, rating, month, count, issnInFile.c_str(), contents);
	}

	ifs.clear();
	ifs.seekg(currPosition, std::ios::beg);
	return nullptr;
}

static Item* getInfoOfItemWithSeries(std::ifstream& ifs, const std::string& isbnOrIssn)
{
	int currPosition = ifs.tellg();

	std::string line;
	while (std::getline(ifs, line)) {
		std::vector<std::string> fields = split(line, ',');

		if (fields.size() < 14) continue;

		std::string id = fields[0];
		std::string author = fields[1];
		std::string title = fields[2];
		std::string publisher = fields[3];
		std::string genre = fields[4];
		std::string description = fields[5];
		int year = parseToInt(fields[6]);
		int month = parseToInt(fields[7]);
		int count = parseToInt(fields[8]);
		int rating = parseToInt(fields[9]);
		std::vector<std::string> keyWords = split(fields[10], ';');
		std::string isbn = fields[11];
		std::string issn = fields[12];

		// Може да търсим по ISBN или ISSN
		if (isbnOrIssn != isbn && isbnOrIssn != issn)
			continue;

		std::vector<Periodical::Contents> contents;
		std::vector<std::string> rawContents = split(fields[13], ';');

		for (const std::string& entry : rawContents) {
			std::vector<std::string> parts = split(entry, '|');
			if (parts.size() != 3) continue;

			std::vector<std::string> kws = split(parts[2], '&');
			Periodical::Contents article(parts[0], parts[1], kws);
			contents.push_back(article);
		}

		ifs.clear();
		ifs.seekg(currPosition, std::ios::beg);

		return new Series(author, title, publisher, genre, description,
			year, month, count, keyWords, rating,
			isbn.c_str(), issn.c_str(), contents);
	}

	ifs.clear();
	ifs.seekg(currPosition, std::ios::beg);
	return nullptr;
}

Item* Library::getInfoOfItem(const std::string& fileName, const std::string& isbnOrIssn)
{
	if (fileName.empty() || isbnOrIssn.empty())
		return nullptr;

	std::ifstream ifs(fileName);
	if (!ifs.is_open())
		throw std::runtime_error("Can't open file\n");

	if (fileName == "books.txt" && isbnOrIssn.size() == GlobalConstants::SIZE_ISBN) {
		return getInfoOfItemWithISBN(ifs, isbnOrIssn);
	}
	else if (fileName == "newsletters.txt" && isbnOrIssn.size() == GlobalConstants::SIZE_ISSN) {
		return getInfoOfItemWithISSN(ifs, isbnOrIssn);
	}
	else if (fileName == "series.txt") {
		if (isbnOrIssn.size() == GlobalConstants::SIZE_ISBN ||
			isbnOrIssn.size() == GlobalConstants::SIZE_ISSN) {
			return getInfoOfItemWithSeries(ifs, isbnOrIssn);
		}
	}

	ifs.close();
	return nullptr;
}

static Item* readBook(std::ifstream& ifs) 
{
	std::string line = readLine(ifs);

	if (line.empty())
		return nullptr;

	std::vector<std::string> tokens = split(line, ',');

	if (tokens.size() < 10)
		return nullptr;

	try {
		unsigned id = parseToInt(tokens[0]);
		std::string title = tokens[1];
		std::string publisher = tokens[2];
		std::string genre = tokens[3];
		std::string description = tokens[4];
		int yearPublished = parseToInt(tokens[5]);
		int rating = parseToInt(tokens[6]);
		std::string author = tokens[7];
		std::vector<std::string> keywords = split(tokens[8], '~');
		std::string isbn = tokens[9];

		if (!isCorrectISBN(isbn.c_str()))
			return nullptr;

		Book* book = new Book(title, publisher, genre, description,
			yearPublished, rating, author, keywords, isbn.c_str());

		return book;
	}
	catch (...) {
		return nullptr;
	}
}

static Item* readPeriodical(std::ifstream& ifs) {
	std::string line;
	std::getline(ifs, line);

	auto parts = split(line, '|');
	auto header = split(parts[0], ',');

	if (header.size() < 10)
		throw std::runtime_error("Invalid periodical format!");

	std::string title = header[1];
	std::string publisher = header[2];
	std::string genre = header[3];
	std::string description = header[4];
	int year = parseToInt(header[5]);
	int rating = parseToInt(header[6]);
	int month = parseToInt(header[7]);
	int count = parseToInt(header[8]);
	std::string issn = header[9];

	std::vector<Periodical::Contents> contents;
	for (size_t i = 1; i < parts.size(); ++i) {
		auto fields = split(parts[i], '`');
		if (fields.size() < 3) continue;
		auto kw = split(fields[2], '^');
		contents.emplace_back(fields[0], fields[1], kw);
	}

	return new Periodical(title, publisher, genre, description, year, rating, month, count, issn.c_str(), contents);
}

static Item* readSeries(std::ifstream& ifs) {
	std::string line;
	std::getline(ifs, line);

	auto parts = split(line, '|');
	auto header = split(parts[0], ',');

	if (header.size() < 13)
		throw std::runtime_error("Invalid series format!");

	std::string title = header[1];
	std::string publisher = header[2];
	std::string genre = header[3];
	std::string description = header[4];
	int year = parseToInt(header[5]);
	int rating = parseToInt(header[6]);
	int month = parseToInt(header[7]);
	int count = parseToInt(header[8]);
	std::string issn = header[9];
	std::string author = header[10];
	std::vector<std::string> keyWords = split(header[11], '~');
	std::string isbn = header[12];

	std::vector<Periodical::Contents> contents;
	for (size_t i = 1; i < parts.size(); ++i) {
		auto fields = split(parts[i], '`');
		if (fields.size() < 3) continue;
		auto kw = split(fields[2], '^');
		contents.emplace_back(fields[0], fields[1], kw);
	}

	return new Series(author, title, publisher, genre, description, year, month, count, keyWords, rating, isbn.c_str(), issn.c_str(), contents);
}

std::vector<Item*> Library::getItemsFromFile(const std::string& filename) const
{
	if (filename.empty())
		throw std::invalid_argument("Invalid filename\n");

	std::ifstream ifs(filename);

	if (!ifs.is_open())
		throw std::runtime_error("Can't open file\n");

	std::vector<Item*> result;

	while (!ifs.eof()) {
		if (filename == "books.txt") {
			result.push_back(readBook(ifs));
		}
		else if (filename == "series.txt") {
			result.push_back(readSeries(ifs));
		}
		else if (filename == "newsletters.txt") {
			result.push_back(readPeriodical(ifs));
		}
	}

	ifs.close();

	return result;
}

void Library::serialize() const
{
	std::ofstream usersAll("users.txt");
	std::ofstream readers("readers.txt");
	std::ofstream admins("administrators.txt");

	for (const User* user : users) {
		if (!user) continue;

		user->saveAllToFile(usersAll);

		if (user->getType() == "Reader")
			user->saveAllToFile(readers);
		else if (user->getType() == "Administrator")
			user->saveAllToFile(admins);
	}

	std::ofstream itemsAll("items.txt");
	std::ofstream books("books.txt");
	std::ofstream newsletters("newsletters.txt");
	std::ofstream series("series.txt");

	for (const Item* item : items) {
		if (!item) continue;

		item->saveAllToFile(itemsAll);

		std::string type = item->getType();
		if (type == "Book")
			item->saveAllToFile(books);
		else if (type == "Periodical")
			item->saveAllToFile(newsletters);
		else if (type == "Series")
			item->saveAllToFile(series);
	}

	usersAll.close();
	readers.close();
	admins.close();
	itemsAll.close();
	books.close();
	newsletters.close();
	series.close();
}

void Library::deserialize()
{
	std::ifstream usersAll("users.txt");
	std::ifstream readers("readers.txt");
	std::ifstream admins("administrators.txt");
	std::ifstream itemsAll("items.txt");
	std::ifstream books("books.txt");
	std::ifstream newsletters("newsletters.txt");
	std::ifstream series("series.txt");

	if (!usersAll.is_open() || !readers.is_open() || !admins.is_open() || !itemsAll.is_open() || !books.is_open() || !newsletters.is_open() || !series.is_open())
		throw std::runtime_error("Failed to open one or more input files");

	std::string line;

	// --- Deserialize users ---
	while (std::getline(readers, line)) {
		if (line.empty()) 
			continue;

		User* reader = Reader::loadFromFile(line);  // static function that returns new Reader*
		if (reader)
			users.push_back(reader);
	}

	while (std::getline(admins, line)) {
		if (line.empty()) 
			continue;

		User* admin = Administrator::loadFromFile(line);  // static function that returns new Administrator*
		if (admin)
			users.push_back(admin);
	}

	// --- Deserialize items ---
	while (std::getline(books, line)) {
		if (line.empty()) 
			continue;

		Item* book = Book::loadFromFile(line);  // static function that returns new Book*
		if (book)
			items.push_back(book);
	}

	while (std::getline(newsletters, line)) {
		if (line.empty())
			continue;

		Item* periodical = Periodical::loadFromFile(line);
		if (periodical)
			items.push_back(periodical);
	}

	while (std::getline(series, line)) {
		if (line.empty()) 
			continue;

		Item* seriesItem = Series::loadFromFile(line);
		if (seriesItem)
			items.push_back(seriesItem);
	}

	usersAll.close();
	readers.close();
	admins.close();
	itemsAll.close();
	books.close();
	newsletters.close();
	series.close();
}

std::vector<Item*> Library::getOnlyOneTypeOfItem(const std::string& typeItem) const
{
	std::vector<Item*> result;
	for (Item* item : items) {
		if (item && item->getType() == typeItem) //or use dynamic_cast
			result.push_back(item);
	}
	return result;
}

std::vector<User*> Library::getOnlyOneTypeOfUser(const std::string& typeUser) const
{
	std::vector<User*> result;
	for (User* user : users) {
		if (user && user->getType() == typeUser) //or use dynamic_cast
			result.push_back(user);
	}
	return result;
}

void Library::copyDynamic(const Library& other)
{
	for (User* u : other.users)
		users.push_back(u->clone()); //return deep copy

	for (Item* i : other.items)
		items.push_back(i->clone());

	currentLoggedUser = nullptr;

	if (other.currentLoggedUser != nullptr)
	{
		for (User* u : users)
		{
			if (u->getUsername() == other.currentLoggedUser->getUsername())
			{
				currentLoggedUser = u;
				break;
			}
		}
	}
}

void Library::freeDynamic()
{
	for (User* user : users)
		delete user;
	users.clear();

	for (Item* item : items)
		delete item;
	items.clear(); 

	currentLoggedUser = nullptr;
}
