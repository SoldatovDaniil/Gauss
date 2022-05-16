#pragma once
#include "StartIncluder.h"



class Vector
{
	double *data = 0;
	int n = 0;

public:

	Vector();
	Vector(int len);
	Vector(const Vector& v);
	~Vector();

	void resize(int newSize);
	void print() const;
	int getSize() const;

	Vector& operator=(const Vector& v);
	Vector operator+(const Vector& v) const;
	Vector operator-(const Vector& v) const;
	Vector& operator+=(const Vector& v);
	Vector& operator-=(const Vector& v);
	Vector operator*(double c) const;
	Vector& operator*=(double c);

	friend Vector operator*(double a, const Vector& v);
	friend bool operator==(const Vector& v1, const Vector& v2);
	friend bool operator!=(const Vector& v1, const Vector& v2);
	friend std::ostream& operator<<(std::ostream& out, const Vector& v);
	
	double& operator[](int i);
	double operator[](int i) const;

};
