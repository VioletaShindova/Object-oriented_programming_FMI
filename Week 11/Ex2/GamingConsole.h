#pragma once
#include "Computer.h"

class GamingConsole : public Computer
{
	~GamingConsole() noexcept;
	void typeOfComputer() const override {
		std::cout << "Type: Gaming Console" << std::endl;
	}

	void peripheralsToConnectTo() const override {
		std::cout << "Connects to: Joystick, monitor" << std::endl;
	}
};

