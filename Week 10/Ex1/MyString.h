#pragma once

class MyString
{
public:
	MyString();

	MyString(const char* arr);

	MyString(const MyString& other);

	MyString& operator=(const MyString& other);

	~MyString();

	void setArray(const char* arr);

	const char* c_str() const;

	char at(unsigned index);

	char front();

	char back();

	size_t size();

	size_t capacity();

	bool empty() const;

	void append(const char* newString);

	void clear();

	bool equals(const MyString& otherArr) const;

	int find(char symbol) const;

	int find(const char* str) const;

	void print() const;

private:
	bool hasSubString(const char* arr, const char* pattern, int& index) const;

	void freeDynamic();

	void copyDynamic(const MyString& other);

	char* arr;
	size_t sizeArr;
	size_t capacityArr;
};

