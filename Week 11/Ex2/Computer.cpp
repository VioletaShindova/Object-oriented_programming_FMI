#include "Computer.h"

void Computer::copyDynamic(const Computer& other)
{
	_modelVideoCard = new (std::nothrow) char[strlen(other._modelVideoCard) + 1];

	if (!_modelVideoCard)
		throw std::bad_alloc();

	strcpy(_modelVideoCard, other._modelVideoCard);
}

void Computer::freeDynamic() noexcept
{
	delete[] _modelVideoCard;
	_modelVideoCard = nullptr;
}

Computer::Computer() : Computer(0, "unknown", 0, 0) {}

Computer::Computer(double _processorPower, const char* _modelVideoCard, int _powerSupplyWattage, int _amountRAM)
{

	setProcessorPower(_processorPower);
	setPowerSupplyWattage(_powerSupplyWattage);
	setAmountRAM(_amountRAM);
	setModelVideoCard(_modelVideoCard);
	
}

Computer::Computer(const Computer& other) : _processorPower(other._processorPower), _powerSupplyWattage(other._powerSupplyWattage), _amountRAM(other._amountRAM)
{
	copyDynamic(other);
}

Computer& Computer::operator=(const Computer& other)
{
	if (this != &other) {
		freeDynamic();
		copyDynamic(other);

		_processorPower = other._processorPower;
		_powerSupplyWattage = other._powerSupplyWattage;
		_amountRAM = other._amountRAM;
	}
	return *this;
}

Computer::~Computer() noexcept
{
	std::cout << "~Computer()" << std::endl;
	freeDynamic();
}

bool Computer::setProcessorPower(double processorPower)
{
	if (processorPower < 0)
		throw std::invalid_argument("Processor must be above 0");

	_processorPower = processorPower;
	return true;
}

bool Computer::setModelVideoCard(const char* modelVideoCard)
{
	if (!modelVideoCard)
		return false;

	char* temp = new (std::nothrow) char[strlen(modelVideoCard) + 1];

	if (!temp)
		throw std::bad_alloc();

	strcpy(temp, modelVideoCard);
	delete[] _modelVideoCard;
	_modelVideoCard = temp;

	return true;
}

bool Computer::setPowerSupplyWattage(int powerSupplyWattage)
{
	if (powerSupplyWattage < 0)
		throw std::invalid_argument("Power of supply wattage must be above 0");

	_powerSupplyWattage = powerSupplyWattage;
	return true;
}

bool Computer::setAmountRAM(int amountRAM)
{
	if (amountRAM < 0)
		throw std::invalid_argument("Amount of RAM must be above 0");

	_amountRAM = amountRAM;
	return true;
}
