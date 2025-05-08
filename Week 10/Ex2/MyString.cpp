#include "MyString.h"
#include <iostream>
#pragma warning(disable : 4996)

MyString::MyString() : MyString("") {}

MyString::MyString(const char* arr) : sizeArr(strlen(arr)), capacityArr(strlen(arr) * 2) {
	setArray(arr);
}

MyString::MyString(const MyString& other) : sizeArr(other.sizeArr), capacityArr(other.capacityArr){
	copyDynamic(other);
}

MyString& MyString::operator=(const MyString& other) {
	if (this != &other) {
		sizeArr = other.sizeArr;
		capacityArr = other.capacityArr;
		freeDynamic();
		copyDynamic(other);
	}

	return *this;
}

MyString::~MyString() {
	freeDynamic();
}

void MyString::setArray(const char* arr) {
	if (!arr)
		throw std::invalid_argument("Empty array!");

	this->arr = new char[sizeArr + 1];
	strcpy(this->arr, arr);
}

const char* MyString::c_str() const {
	return arr;
}

char MyString::at(unsigned index) {
	return arr[index];
}

char MyString::front() {
	return arr[0];
}

char MyString::back() {
	return arr[this->sizeArr - 1];
}

size_t MyString::size() {
	return this->sizeArr;
}

size_t MyString::capacity() {
	return this->capacityArr;
}

bool MyString::empty() const {
	return !arr || this->sizeArr == 0;
}

void MyString::append(const char* newString) {
	if (sizeArr + strlen(newString) + 1 >= capacityArr)
		resize();

	char* temp = new char[sizeArr + strlen(newString) + 1];

	strcpy(temp, arr);
	strcpy(temp + sizeArr, newString);

	freeDynamic();
	arr = temp;
	sizeArr += strlen(newString);
}

void MyString::clear() {
	freeDynamic();
	sizeArr = 0;
}

bool MyString::equals(const MyString& otherArr) const {
	return strcmp(arr, otherArr.arr) == 0;
}

int MyString::find(char symbol) const {
	int index = 0;
	while (arr[index] != '\0') {
		if (arr[index] == symbol)
			return index;
		index++;
	}
	index = -1;
	return index;
}

int MyString::find(const char* str) const {
	int index = 0;
	if (hasSubString(arr, str, index))
		return index - strlen(str) + 1;
	index = -1;
	return index;
}

void MyString::print() const {
	std::cout << "arr\n";
}

void MyString::resize(){
	size_t capacityArrTemp = capacityArr * 2;
	char* tempArr = new char[capacityArrTemp];

	strcpy(tempArr, arr);

	freeDynamic();
	arr = tempArr;
	sizeArr = capacityArr;
	capacityArr = capacityArrTemp;
}

bool MyString::hasSubString(const char* arr, const char* pattern, int& index) const {
	size_t textLen = strlen(arr);
	size_t patternLen = strlen(pattern);

	for (size_t i = 0; i <= textLen - patternLen; ++i) {
		if (strncmp(arr + i, pattern, patternLen) == 0) {
			index = i + patternLen - 1;
			return true;
		}
	}
	
	return false;
}

void MyString::freeDynamic() {
	delete[] arr;
	arr = nullptr;
}

void MyString::copyDynamic(const MyString& other) {
	arr = new char[strlen(other.arr) + 1];
	strcpy(arr, other.arr);
}


bool operator==(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.arr, rhs.arr) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs) {
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const MyString& obj) {
	os << obj.arr;
	return os;
}

std::istream& operator>>(std::istream& is, MyString& obj) {
	is >> obj.sizeArr;

	obj.arr = new char[obj.sizeArr + 1];

	obj.arr[obj.sizeArr] = '\0';

	is >> obj.capacityArr;
	return is;
}

bool operator<(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.arr, rhs.arr) < 0;
}

bool operator>(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.arr, rhs.arr) > 0;
}