#pragma once
#include "StartIncluder.h"

class Matrix
{
	Vector* data = 0;
	int m = 0;
	int n = 0;

public:

	Matrix();
	Matrix(int m, int n);
	~Matrix();
	Matrix(const Matrix& m1);

	Matrix& operator=(const Matrix& other);
	Matrix& operator+=(const Matrix& other);
	Vector& operator[](int a);
	Matrix operator+(const Matrix& other) const;
	Matrix operator-(const Matrix& other) const;
	Matrix& operator-=(const Matrix& other);
	Matrix operator*(double c) const;
	Matrix& operator*=(double c);
	Matrix operator*(const Matrix& other) const;

	friend bool operator==(const Matrix& m1, const Matrix& m2);
	friend bool operator!=(const Matrix& m1, const Matrix& m2);


	int rank();
	int getM();
	int getN();

	void traengl();
	Matrix trans();
	void resize(int newM, int newN);
	void print() const;
	void swap(int row1, int row2, int N);
};