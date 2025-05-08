#include "MyString.h"
#include <iostream>
#pragma warning(disable : 4996)

MyString::MyString(const char* arr) {
	setArray(arr);
}

MyString::MyString(const MyString& other) : size(other.size) {
	copyDynamic(other);
}

MyString& MyString::operator=(const MyString& other) {
	if (this != &other) {
		this->size = other.size;
		freeDynamic();
		copyDynamic(other);
	}
		return *this;
}

MyString::~MyString() {
	freeDynamic();
}

void MyString::setArray(const char* arr) {
	this->size = strlen(arr);
	this->arr = new (std::nothrow) char[this->size + 1];
	if (!this->arr)
		throw std::out_of_range("Not enough capacity!");

	strcpy(this->arr, arr);
}

char MyString::at(int index) const {
	if (!isValidIndex(index))
		throw std::invalid_argument("Invalid index!");

	return this->arr[index];
}

char MyString::front() const {
	return this->arr[0];
}
char MyString::back() const {
	return this->arr[this->size - 1];
}

//c_str()
const char* MyString::getArray() const {
	return this->arr;
}

//size()
size_t MyString::getSize() const {
	return this->size;
}

//it is not very correct since you can change the value when you should be using setSize() instead because of the checks
//size_t& getSize() {
//	return this->size;
//}

//returns const to the copy which is unnecessary
//const size_t getSize() const {
//	return this->size;
//}

//for an object like std::string, std::vector, class etc. but not a primitive type
//const size_t& getSize() {
//	return this->size;
//}

bool MyString::isEmpty() const {
	return (!this->arr) || (this->size == 0);
}

bool MyString::append(const char* arr) {
	if (!arr)
		return false;

	if (this->size + strlen(arr) + 1 >= this->size) {
		char* temp;
		size_t tempSize = this->size + strlen(arr)+ 1;
		temp = new char[tempSize];

		strcpy(temp, this->arr);
		strcpy(temp + this->size, arr);
		this->size = tempSize;
		freeDynamic();
		this->arr = new char[tempSize];
		strcpy(this->arr, temp);
		delete[] temp;
		return true;
	}

	strcpy(this->arr + this->size, arr);

	return true;
}

void MyString::clear() {
	freeDynamic();
}

int MyString::find(char symbol) const {
	for (size_t i = 0; i < this->size; i++) {
		if (this->arr[i] == symbol)
			return 1;
	}
	return -1;
}

int MyString::find(const char* str) const {
	size_t newStrSize = strlen(str);

	for (size_t i = 0; i < this->size; i++) {
		if (hasSubstring(this->arr + i, str, newStrSize))
			return 1;
	}

	return -1;
}

void MyString::print() const {
	std::cout << this->arr;
}

void MyString::copyDynamic(const MyString& other) {
	this->arr = new char[other.size + 1];
	strcpy(this->arr, other.arr);
}

void MyString::freeDynamic() {
	delete[] arr;
}

bool MyString::isValidIndex(int index) const {
	return (0 <= index) && (index < this->size);
}

//"ABC" == "ABC"
int equals(const MyString& lhs, const MyString& rhs) {
	const char* leftArr = lhs.getArray();
	const char* rightArr = rhs.getArray();

	while (*leftArr && *rightArr) {
		if ((*(leftArr + 1) == '\0') && (*(rightArr + 1) == '\0'))
			return 0;

		if ((*leftArr) < (*rightArr))
			return -1;
		else if ((*leftArr) > (*rightArr))
			return 1;

		leftArr++;
		rightArr++;
	}

	if (*leftArr)
		return 1;
	else
		return -1;
}

bool hasSubstring(const char* str1, const char* str2, size_t str2Len) {
	for (size_t i = 0; i < str2Len; i++) {
		if (str1[i] == '\0')
			return false;

		if (str1[i] != str2[i])
			return false;
	}

	return true;
}