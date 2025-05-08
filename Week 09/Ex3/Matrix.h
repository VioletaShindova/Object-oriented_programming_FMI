#pragma once
#include <iostream>

//задължително вътрешни
//function call operator()
//operator bool
//[] 
//=

class Matrix
{
public:
	Matrix();

	Matrix(int rows, int columns);

	Matrix(const Matrix& other);

	Matrix& operator=(const Matrix& other);

	~Matrix();

	void setRows(int rows);

	void setCols(int columns);

	void setElements(size_t rows, size_t columns);

	size_t getRows();

	size_t getRowsConst() const;

	size_t getCols();

	size_t getColsConst() const;

	int** getElements();

	int** getElementsConst() const;

	int getSumOfElements() const;

	Matrix& operator+=(const Matrix& rhs);

	Matrix& operator-=(const Matrix& rhs);

	Matrix& operator++();

	Matrix operator++(int);

	Matrix& operator--();

	Matrix operator--(int);

	Matrix& operator*=(int number);

	Matrix& operator*=(const Matrix& rhs);

	int* operator[](size_t col);

	friend bool isCountOfColsEqualToCountOfRows(const Matrix& lhs, const Matrix& rhs);

	friend bool operator==(const Matrix& lhs, const Matrix& rhs);

	friend bool operator!=(const Matrix& lhs, const Matrix& rhs);

	Matrix operator()() const;

	operator bool() const;

	friend std::ostream& operator<<(std::ostream& os, const Matrix& rhs);

	friend std::istream& operator>>(std::istream& is, Matrix& rhs);

private:
	int getSumOfEachMultiplyingBetweenMatrixes(const Matrix& lhs, const Matrix& rhs, size_t row, size_t col);
	void freeDynamic();
	void copyDynamic(const Matrix& other);

	int** elements;
	size_t rows;
	size_t cols;
};

Matrix operator+(const Matrix& lhs, const Matrix& rhs);

Matrix operator-(const Matrix& lhs, const Matrix& rhs);

Matrix operator*(const Matrix& lhs, int number);

Matrix operator*(int number, const Matrix& rhs);

Matrix operator*(const Matrix& lhs, const Matrix& rhs);

bool operator<(const Matrix& lhs, const Matrix& rhs);

bool operator<=(const Matrix& lhs, const Matrix& rhs);

bool operator>(const Matrix& lhs, const Matrix& rhs);

bool operator>=(const Matrix& lhs, const Matrix& rhs);