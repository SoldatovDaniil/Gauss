#include "Vector.h"


void Vector::print() const
{
	std::cout << "[";

	for (int i = 0; i < n - 1; i++)
	{
		std::cout<< data[i] << " ";
	}
	std::cout << data[n - 1] << "]" << std::endl;
}

Vector::Vector()
{
	data = 0;
	n = 0;
}

Vector::Vector(int len)
{
	data = new double[len];
	for (int i = 0; i < len; i++)
	{
		data[i] = 0;
	}
	n = len;
}

Vector::Vector(const Vector& v)
{
	this->resize(v.n);
	for (int i = 0; i < n; i++)
	{
		data[i] = v.data[i];
	}
}

Vector::~Vector()
{
	delete[] data;
	data = 0;
	n = 0;
}

Vector& Vector::operator+=(const Vector& v)
{
	if (this->n != v.n)
	{
		std::cout << "ERROR in Vector::operator+=" << std::endl;
		return *this;
	}
	for (int i = 0; i < n; i++)
	{
		data[i] += v.data[i];
	}
	return *this;
}

double& Vector::operator[](int i)
{
	return data[i];
}

double Vector::operator[](int i) const
{
	return data[i];
}

Vector Vector::operator+(const Vector& v) const
{
	if (n != v.n)
	{
		std::cout << "ERROR in Vector::operator+" << std::endl;
		return Vector();
	}
	Vector r(n);
	for (int i = 0; i < n; i++)
	{
		r[i]= v[i] + data[i];
	}
	return r;
}

void Vector::resize(int newSize)
{
	delete[] data;
	data = new double[newSize];
	this->n = newSize;
	for (int i = 0; i < n; i++)
	{
		data[i] = 0;
	}
}

Vector& Vector::operator=(const Vector& v)
{
	if (this->n != v.n)
	{
		this->resize(v.n);
	}
	for (int i = 0; i < n; i++)
	{
		data[i] = v.data[i];
	}
	return *this;
}

Vector Vector::operator-(const Vector& v) const
{
	if (n != v.n)
	{
		std::cout << "ERROR in Vector::operator-" << std::endl;
		return Vector();
	}
	Vector r(n);
	for (int i = 0; i < n; i++)
	{
		r[i] = data[i] - v.data[i];
	}
	return r;
}

Vector& Vector::operator-=(const Vector& v)
{
	if (this->n != v.n)
	{
		std::cout << "ERROR in Vector::operator-=" << std::endl;
		return *this;
	}
	for (int i = 0; i < n; i++)
	{
		data[i] -= v.data[i];
	}
	return *this;
}

Vector Vector::operator*(double c) const
{
	Vector r(n);
	for (int i = 0; i < n; i++)
	{
		r[i] = data[i] * c;
	}
	return r;
}

Vector& Vector::operator*=(double c)
{
	for (int i = 0; i < n; i++)
	{
		data[i] *= c;
	}
	return *this;
}

Vector operator*(double a, const Vector& v)
{
	return v * a;
}

std::ostream& operator<<(std::ostream& out, const Vector& v)
{
	out << "(";
	for (int i = 0; i < v.n - 1; i++)
	{
		out << v.data[i] << ", ";
	}
	out << v.data[v.n - 1] << ")" << std::endl;
	return out;
}

bool operator==(const Vector& v1, const Vector& v2)
{
	if (v1.n != v2.n)
	{
		return 0;
	}

	for (int i = 0; i < v1.n; i++)
	{
		if (v1.data[i] != v2.data[i])
		{
			return 0;
		}
	}

	return 1;
}

bool operator!=(const Vector& v1, const Vector& v2)
{
	if (v1.n == v2.n)
	{
		return 0;
	}

	for (int i = 0; i < v1.n; i++)
	{
		if (v1.data[i] == v2.data[i])
		{
			return 0;
		}
	}

	return 1;
}

int Vector::getSize() const
{
	return n;
}