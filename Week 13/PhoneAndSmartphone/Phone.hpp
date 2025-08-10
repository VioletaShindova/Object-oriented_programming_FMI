#pragma once

#ifndef __PHONE_HEADER_INCLUDED_

#define __PHONE_HEADER_INCLUDED_

class Phone
{
public:
	Phone();
	Phone(const char* model, const char* brand, double price = 0);
	Phone(const Phone& other);
	Phone& operator=(const Phone& other);
	virtual ~Phone() noexcept;

	inline const char* getModel() const noexcept { return model; }
	inline const char* getBrand() const noexcept { return brand; }
	inline double getPrice() const noexcept { return price; }

	void setModel(const char* model);
	void setBrand(const char* brand);
	void setPrice(double price);

protected:
	mutable double price;

private:
	void copyDynamic(const Phone& other);
	void freeDynamic();

	char* model;
	char* brand;
};

bool areEqual(const Phone& lhs, const char* model, const char* brand);

#endif