#pragma once
#include "Computer.h"

class PC : public Computer
{
	~PC() noexcept;

	void typeOfComputer() const override {
		std::cout << "Type: PC" << std::endl;
	}
	void peripheralsToConnectTo() const override {
		std::cout << "Connects to: mouse, keyboard, microphone, headphones" << std::endl;
	}
};

