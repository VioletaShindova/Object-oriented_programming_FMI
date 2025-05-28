#pragma once
#include <iostream>
#pragma warning(disable : 4996)

class Computer
{
public:
	Computer();
	Computer(double _processorPower, const char* _modelVideoCard, int _powerSupplyWattage, int _amountRAM);
	Computer(const Computer& other);
	Computer& operator=(const Computer& other);
	virtual ~Computer() noexcept;

	bool setProcessorPower(double processorPower);
	bool setModelVideoCard(const char* modelVideoCard);
	bool setPowerSupplyWattage(int powerSupplyWattage);
	bool setAmountRAM(int amountRAM);

	virtual void typeOfComputer() const = 0; // функцията няма дефиниция в този клас и задължително трябва да бъде предефинирана (override-ната) в наследниците
	virtual void peripheralsToConnectTo() const = 0;

protected:
	double _processorPower;
	char* _modelVideoCard;
	unsigned _powerSupplyWattage;
	unsigned _amountRAM;

private:
	void copyDynamic(const Computer& other);
	void freeDynamic() noexcept;
};

