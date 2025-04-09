#pragma once

class MyString 
{
public:
	MyString() : MyString("") {}

	explicit MyString(const char* arr);

	MyString(const MyString& other);

	MyString& operator=(const MyString& other);

	~MyString();

	void setArray(const char* arr);

	char at(int index) const;

	char front() const;

	char back() const;

	const char* getArray() const;

	size_t getSize() const;

	bool isEmpty() const;

	bool append(const char* arr);

	void clear();

	int find(char symbol) const;

	int find(const char* str) const;

	void print() const;

private:
	void copyDynamic(const MyString& other);

	void freeDynamic();

	bool isValidIndex(int index) const;

	char* arr;
	size_t size;
};

int equals(const MyString& lhs, const MyString& rhs);

bool hasSubstring(const char* str1, const char* str2, size_t str2Len);