#include "PowerString.hpp"
#include "ElectricalAppliance.hpp"

PowerString::PowerString() : PowerString(1) {}

PowerString::PowerString(int countNest) : electricals(nullptr), currentElectricals(0), maxPower(1000)
{
	setNests(countNest);
}

PowerString::PowerString(int countNest, int maxPower) : electricals(nullptr), currentElectricals(0)
{
	setNests(countNest);
	setMaxPower(maxPower);
}

PowerString::PowerString(const PowerString& other) 
	: electricals(nullptr), currentElectricals(other.currentElectricals), countNest(other.countNest), maxPower(other.maxPower)
{
	copyDynamic(other);
}

PowerString::~PowerString()
{
	freeDynamic();
}

static void turnOffAllDevices(ElectricalAppliance** devices, size_t currentDevices)
{
	if (!devices)
		throw std::logic_error("Can't turn off devices when there aren't any plugged in\n");

	for (size_t i = 0; i < currentDevices; i++)
		devices[i]->setStatus(false);
}

void PowerString::turnOnDevice(const ElectricalAppliance* device)
{
	if (!device || !countNest) //meaning if count nest is 0 there is no space for a device to be plugged in
		throw std::invalid_argument("Can't turn on the device\n");

	ElectricalAppliance* tempElectric = new (std::nothrow) ElectricalAppliance(*device);

	if (!tempElectric)
		throw std::bad_alloc();

	if (currentElectricals + 1 > countNest)
		throw std::logic_error("Nest is full of electrical appliances\n");

	if (currentUsedElectric + tempElectric->getPower() > maxPower)
	{
		turnOffAllDevices(electricals, currentElectricals);
		currentUsedElectric = 0;
		maxPower = 0;
		return;
	}

	electricals[currentElectricals] = tempElectric;
	electricals[currentElectricals++]->setStatus(true);
	currentUsedElectric += tempElectric->getPower();
	countNest--;
}

void PowerString::turnOffDevice(const ElectricalAppliance* device)
{
	if (!device || !device->getStatus())
		throw std::invalid_argument("Can't turn off the given device");

	for (size_t i = 0; i < currentElectricals; i++)
	{
		if(areEqual(electricals[i], device))
		{
			electricals[i]->setStatus(false);
			currentUsedElectric -= device->getPower();
			countNest++;
		}
	}
}

void PowerString::writeToStream(std::ostream& os)
{
	if (!os.good())
		throw std::runtime_error("Stream is not good\n");

	os << countNest << ", " << maxPower << ", "
}

void PowerString::freeDynamic()
{
	for (size_t i = 0; i < countNest; i++)
	{
		delete electricals[i];
	}

	delete[] electricals;
	electricals = nullptr;
}

void PowerString::copyDynamic(const PowerString& other)
{
	ElectricalAppliance** temp = new (std::nothrow) ElectricalAppliance * [other.countNest];

	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < other.countNest; i++)
	{
		temp[i] = new (std::nothrow) ElectricalAppliance(*other.electricals[i]);

		if (!temp[i])
		{
			for (size_t j = i - 1; j >= 0; j++)
				delete temp[i];
			delete[] temp;
			throw std::bad_alloc();
		}
	}

	for (size_t i = 0; i < countNest; i++)
		delete electricals[i];
	delete[] electricals;
	electricals = temp;
}

void PowerString::setNests(int countNest)
{
	if (countNest < 0)
		throw std::invalid_argument("Nest count must be a positive number\n");

	ElectricalAppliance** temp = new (std::nothrow) ElectricalAppliance * [countNest];
	
	if (!temp)
		throw std::bad_alloc();

	for (size_t i = 0; i < countNest; i++)
	{
		temp[i] = new (std::nothrow) ElectricalAppliance();
		if (!temp[i]) {
			for (int j = i - 1; j >= 0; j--)
				delete temp[j];

			delete[] temp;
			throw std::bad_alloc();
		}
	}

	for (size_t i = 0; i < this->countNest; i++)
		delete electricals[i];

	delete[] electricals;
	electricals = temp;

	this->countNest = countNest;
}

void PowerString::setMaxPower(int maxPower)
{
	if (maxPower < 0)
		throw std::invalid_argument("Max power must be a positive number\n");

	this->maxPower = maxPower;
}
