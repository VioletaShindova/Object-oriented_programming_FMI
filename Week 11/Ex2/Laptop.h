#pragma once
#include "Computer.h"

class Laptop : public Computer
{
	~Laptop() noexcept;
	void typeOfComputer() const override {
		std::cout << "Type: Laptop" << std::endl;
	}

	void peripheralsToConnectTo() const override {
		std::cout << "Connects to: Mouse pad, keyboard, monitor" << std::endl;
	}
};

