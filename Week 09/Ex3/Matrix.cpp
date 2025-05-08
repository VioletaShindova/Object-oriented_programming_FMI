#include "Matrix.h"

Matrix::Matrix() : Matrix(2, 2) {}

Matrix::Matrix(int rows, int columns) {
	setRows(rows);
	setCols(columns);
	setElements(rows, columns);
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
	copyDynamic(other);
}

Matrix& Matrix::operator=(const Matrix& other) {
	if (this != &other) {
		rows = other.rows; 
		cols = other.cols;
		freeDynamic();
		copyDynamic(other);
	}

	return *this;
}

Matrix::~Matrix() {
	freeDynamic();
}

void Matrix::setRows(int rows) {
	if (0 >= rows)
		throw std::invalid_argument("Invalid size of rows");

	this->rows = rows;
}

void Matrix::setCols(int columns) {
	if (0 >= columns)
		throw std::invalid_argument("Invalid size of columns");

	this->cols = columns;
}

void Matrix::setElements(size_t rows, size_t columns) {
	elements = new int* [rows];

	for (size_t i = 0; i < rows; i++) {
		elements[i] = new int[columns];
		for (size_t j = 0; j < cols; j++) {
			elements[i][j] = 0;
		}
	}
}

size_t Matrix::getRows() {
	return rows;
}

size_t Matrix::getRowsConst() const {
	return rows;
}

size_t Matrix::getCols() {
	return cols;
}

size_t Matrix::getColsConst() const {
	return cols;
}

int** Matrix::getElements() {
	return elements;
}

int** Matrix::getElementsConst() const {
	return elements;
}

int Matrix::getSumOfElements() const {
	int sum = 0;
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++)
			sum += elements[i][j];
	}
	return sum;
}

Matrix& Matrix::operator+=(const Matrix& rhs) {
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++)
			elements[i][j] += rhs.elements[i][j];
	}

	return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs) {
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++)
			elements[i][j] -= rhs.elements[i][j];
	}

	return *this;
}

//prefix
Matrix& Matrix::operator++() {
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++)
			++elements[i][j];
	}
	return *this;
}

//postfix
Matrix Matrix::operator++(int) {
	Matrix temp(*this);
	++(*this);
	return temp;
}

Matrix& Matrix::operator--() {
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++)
			--elements[i][j];
	}

	return *this;
}

Matrix Matrix::operator--(int) {
	Matrix temp(*this);
	--(*this);
	return temp;
}

Matrix& Matrix::operator*=(int number) {
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++)
			elements[i][j] *= number;
	}

	return *this;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {
	Matrix result(rows, rhs.cols);  

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < rhs.cols; j++) {
			result.elements[i][j] = getSumOfEachMultiplyingBetweenMatrixes(*this, rhs, i, j); 
		}
	}

	*this = result;  

	return *this;
}

int* Matrix::operator[](size_t col) {
	return elements[col];
}

bool isCountOfColsEqualToCountOfRows(const Matrix& lhs, const Matrix& rhs) {
	return lhs.cols == rhs.rows;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
	for (size_t i = 0; i < lhs.rows; i++) {
		for (size_t j = 0; j < lhs.cols; j++) {
			if (lhs.elements[i][j] != rhs.elements[i][j])
				return false;
		}
	}
	return true;
}

bool operator!=(const Matrix& lhs, const Matrix& rhs) {
	return !(lhs == rhs);
}

Matrix Matrix::operator()() const {
	Matrix temp((int)cols, (int)rows);

	for (size_t i = 0; i < cols; i++) {
		for (size_t j = 0; j < rows; j++)
			temp.elements[i][j] = elements[j][i];
	}

	return temp;
}

Matrix::operator bool() const {
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			if (elements[i][j] == 0)
				return false;
		}
	}
	return true;
}

std::ostream& operator<<(std::ostream& os, const Matrix& rhs) {
	for (size_t i = 0; i < rhs.rows; i++) {
		for (size_t j = 0; j < rhs.cols; j++)
			os << rhs.elements[i][j] << " ";
		std::cout << std::endl;
	}
	return os;
}

std::istream& operator>>(std::istream& is, Matrix& rhs) {
	for (size_t i = 0; i < rhs.rows; i++) {
		for (size_t j = 0; j < rhs.cols; j++)
			is >> rhs.elements[i][j];
	}
	return is;
}

int Matrix::getSumOfEachMultiplyingBetweenMatrixes(const Matrix& lhs, const Matrix& rhs, size_t row, size_t col) {
	int sum = 0;
	for (size_t k = 0; k < lhs.getColsConst(); k++)
	{
		sum += (lhs.elements[row][k] * rhs.elements[k][col]);
	}
	return sum;
}

void Matrix::freeDynamic() {
	for (size_t i = 0; i < rows; i++) {
			delete[] elements[i];
	}
	delete[] elements;
	elements = nullptr;
}

void Matrix::copyDynamic(const Matrix& other) {
	elements = new int*[other.rows];

	for (size_t i = 0; i < rows; i++) {
		elements[i] = new int[other.cols];
		for (size_t j = 0; j < cols; j++) {
			elements[i][j] = other.elements[i][j];
		}
	}
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
	Matrix temp(lhs);
	temp += rhs;
	return temp;
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
	Matrix temp(lhs);
	temp -= rhs;
	return temp;
}

Matrix operator*(const Matrix& lhs, int number) {
	Matrix temp(lhs);
	temp *= number;
	return temp;
}

Matrix operator*(int number, const Matrix& rhs) {
	Matrix temp(rhs);
	temp *= number;
	return temp;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
	Matrix temp(lhs);
	if (isCountOfColsEqualToCountOfRows(lhs, rhs))
		temp *= rhs;
	return temp;
}

bool operator<(const Matrix& lhs, const Matrix& rhs) {
	return lhs.getSumOfElements() < rhs.getSumOfElements();
}

bool operator<=(const Matrix& lhs, const Matrix& rhs) {
	return lhs.getSumOfElements() <= rhs.getSumOfElements();
}

bool operator>(const Matrix& lhs, const Matrix& rhs) {
	return lhs.getSumOfElements() > rhs.getSumOfElements();
}

bool operator>=(const Matrix& lhs, const Matrix& rhs) {
	return lhs.getSumOfElements() >= rhs.getSumOfElements();
}