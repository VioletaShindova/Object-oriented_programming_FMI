#include "ElectricalAppliance.hpp"
#include "iohelpers.hpp"

#pragma warning(disable : 4996)

unsigned ElectricalAppliance::currID = 0;

ElectricalAppliance::ElectricalAppliance() : ElectricalAppliance("unknown", "unknown", 0) {}

ElectricalAppliance::ElectricalAppliance(const char* description, const char* brand, double power, bool status, bool active)
	: description(nullptr), brand(nullptr), power(0), status(false), active(false), id(incrementID())
{
	setStatus(status);
	setActive(active);
	setPower(power);
	setBrand(brand);

	try {
		setDescription(description);
	}
	catch (std::bad_alloc& bad_alloc) {
		delete[] this->brand;
		std::cout << "Bad allocation\n";
		throw bad_alloc;
	}
	catch (std::invalid_argument& inv_arg) {
		delete[] this->brand;
		std::cout << inv_arg.what();
		throw inv_arg;
	}
}

ElectricalAppliance::ElectricalAppliance(const ElectricalAppliance& other) 
	: power(other.power), status(false), active(false), id(incrementID())
{
	copyDynamic(other);
}

ElectricalAppliance& ElectricalAppliance::operator=(const ElectricalAppliance& other)
{
	if (this != &other) {
		power = other.power;
		status = false; 
		active = false;

		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}

ElectricalAppliance::~ElectricalAppliance() noexcept
{
	freeDynamic();
}

void ElectricalAppliance::setDescription(const char* description)
{
	if (!description || strlen(description) == 0)
		throw std::invalid_argument("Invalid description\n");

	char* tempDescription = new (std::nothrow) char[strlen(description) + 1];

	if (!tempDescription)
		throw std::bad_alloc();

	strcpy(tempDescription, description);

	delete[] this->description;
	this->description = tempDescription;
}

void ElectricalAppliance::setBrand(const char* brand)
{
	if (!brand || strlen(brand) == 0)
		throw std::invalid_argument("Invalid brand\n");

	char* tempBrand = new (std::nothrow) char[strlen(brand) + 1];

	if (!tempBrand)
		throw std::bad_alloc();

	strcpy(tempBrand, brand);

	delete[] this->brand;
	this->brand = tempBrand;
}

void ElectricalAppliance::setPower(double power)
{
	if (power < 0)
		throw std::invalid_argument("Power must be a positive number\n");

	this->power = power;
}

void ElectricalAppliance::setStatus(bool status)
{
	using std::cin;

	if (!status)
		active = false;
	else {
		char buffer[128];
		cin.getline(buffer, 128);

		if (strlen(buffer) == 0)
			throw std::logic_error("You should type where it is logged in\n");

		//имаме проблем в случай, че description e nullptr
		//не знам дали това трябва така да се направи
		strncat(description, buffer, 128); //състояние – дали е включен в мрежата или не е (plugged in). При включване се указва къде е включен;
	}

	this->status = status;
}

void ElectricalAppliance::setActive(bool active)
{
	if (active && !status)
		throw std::logic_error("Can't make it active while the status is not plugged in\n");

	this->active = active;
}

void ElectricalAppliance::writeToStream(std::ostream& os)
{
	if (!os.good())
		throw std::runtime_error("Stream is not good\n");

	if (!description || !brand)
		throw std::runtime_error("Can't write a nullptr pointer\n");

	//we accept that there are no commas in the description nor the brand name
	os << strlen(description) << ", " << description << ", ";
	
	os << strlen(brand) << ", " << brand << ", " << power << ", " << status << ", " << active << '\n';
}

static void isValidReadFromStream(std::istream& is)
{
	if (!is)
	{
		is.clear();
		is.sync();
		throw std::runtime_error("Invalid information while reading\n");
	}
}

void ElectricalAppliance::readFromStream(std::istream& is)
{
	if (!is.good())
		throw std::runtime_error("Stream is not good\n");

	size_t size;
	is >> size;

	isValidReadFromStream(is);
	skipSpaces(is, ' ');

	char* tempDescription = new (std::nothrow) char[size + 1];
	if (!tempDescription)
		throw std::invalid_argument("Bad allocation\n");
	is.getline(tempDescription, size + 1, ','); //always read to size - 1 because it leaves space for '\0'
	tempDescription[size] = '\0';

	skipSpaces(is, ' ');

	is >> size;
	isValidReadFromStream(is);

	skipSpaces(is, ' ');

	char* tempBrand = new (std::nothrow) char[size + 1];
	if (!tempBrand)
		throw std::invalid_argument("Bad allocation\n");
	is.getline(tempBrand, size + 1, ',');
	tempBrand[size] = '\0';

	skipSpaces(is, ' ');

	double tempPower;
	is >> tempPower;
	isValidReadFromStream(is);
	skipSpaces(is, ' ');

	bool tempStatus;
	is >> tempStatus;
	isValidReadFromStream(is);
	skipSpaces(is, ' ');

	bool tempActive;
	is >> tempActive;
	isValidReadFromStream(is);
	skipSpaces(is, ' ');

	delete[] description;
	description = tempDescription;

	delete[] brand;
	brand = tempBrand;

	power = tempPower;
	status = tempStatus;
	active = tempActive;
}

unsigned ElectricalAppliance::incrementID()
{
	return ++currID;
}

void ElectricalAppliance::copyDynamic(const ElectricalAppliance& other)
{
	char* tempDescription = new (std::nothrow) char[strlen(other.description) + 1];

	if (!tempDescription)
		throw std::bad_alloc();

	strcpy(tempDescription, other.description);

	char* tempBrand = new (std::nothrow) char[strlen(other.brand) + 1];

	if (!tempBrand) {
		delete[] tempDescription;
		throw std::bad_alloc();
	}

	strcpy(tempBrand, other.brand);

	delete[] description;
	description = tempDescription;

	delete[] brand;
	brand = tempBrand;
}

void ElectricalAppliance::freeDynamic()
{
	delete[] description;
	delete[] brand;

	description = nullptr;
	brand = nullptr;
}

bool areEqual(const ElectricalAppliance* lhs, const ElectricalAppliance* rhs)
{
	return strcmp(lhs->getDescription(), rhs->getDescription()) == 0 &&
		strcmp(lhs->getBrand(), rhs->getBrand()) == 0 && 
		lhs->getID() == rhs->getID();
}
