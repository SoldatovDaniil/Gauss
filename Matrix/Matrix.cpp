#include "Matrix.h"


Matrix::Matrix()
{
	m = 0;
	n = 0;
	data = 0;
}

Matrix::Matrix(int m, int n)
{
	this->m = m;
	this->n = n;
	data = new Vector[m];
	for (int i = 0; i < m; i++)
	{
		data[i] = Vector(n);
	}
}

Matrix::Matrix(const Matrix& m1)
{
	this->resize(m1.m, m1.n);
	for (int i = 0; i < m; i++)
	{
		data[i] = m1.data[i];
	}
}

void Matrix::resize(int newM, int newN)
{
	delete[] data;
	data = new Vector[newM];
	this->m = newM;
	this->n = newN;
	
	for (int i = 0; i < m; i++)
	{
		data[i] = Vector(n);
	}
}


Matrix::~Matrix()
{
	delete[] data;
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if ((m != other.m) || (n != other.n))
	{
		this->m = other.m;
		this->n = other.n;
		delete[] data;
		data = new Vector[m];
	}

	for (int i = 0; i < m; i++)
	{
		data[i] = other.data[i];
	}
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& other) 
{
	for (int i = 0; i < m; i++)
	{
		data[i] += other.data[i];
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	for (int i = 0; i < m; i++)
	{
		data[i] -= other.data[i];
	}
	return *this;
}

Vector& Matrix::operator[](int a)
{
	return data[a];
}

Matrix Matrix::operator+(const Matrix& other) const
{
	if (m != other.m || n != other.n)
	{
		std::cout << "ERROR in Vector::operator+"  << std::endl;
		return Matrix();
	}
	Matrix res(m, n);

	for (int i = 0; i < m; i++)
	{
		res[i] = data[i] + other.data[i];
	}

	return res;
}

Matrix Matrix::operator-(const Matrix& other) const
{
	if (m != other.m || n != other.n)
	{
		std::cout << "ERROR in Vector::operator-" << std::endl;
		return Matrix();
	}
	Matrix res(m, n);

	for (int i = 0; i < m; i++)
	{
		res[i] = data[i] - other.data[i];
	}

	return res;
}

Matrix Matrix::operator*(double c) const
{
	Matrix res(m, n);
	for (int i = 0; i < m; i++)
	{
		data[i] *= c; 
	}
}

Matrix& Matrix:: operator*=(double c)
{
	for (int i = 0; i < m; i++)
	{
		data[i] *= c;
	}
	return *this;
}


void Matrix::print() const
{
	for (int i = 0; i < m; i++)
	{
		std::cout << data[i] << std::endl;
	}
}

bool operator==(const Matrix& m1, const Matrix m2)
{
	if (m1.m != m2.m || m1.n != m2.n)
	{
		return 0;
	}
	
	for (int i = 0; i < m1.m; i++)
	{
		if (m1.data[i] != m2.data[i])
		{
			return 0;
		}
	}

	return 1;
}


bool operator!=(const Matrix& m1, const Matrix m2)
{
	if (m1.m == m2.m || m1.n == m2.n)
	{
		return 0;
	}

	for (int i = 0; i < m1.m; i++)
	{
		if (m1.data[i] == m2.data[i])
		{
			return 0;
		}
	}

	return 1;
}

Matrix Matrix::operator*(const Matrix& other) const
{
	if (n != other.m)
	{
		std::cout << "Error in Matrix *" << std::endl;
		return Matrix();
	}

	Matrix res(m, other.n);

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < other.n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				res[i][j] += data[i][k] * other.data[k][j];
			}
		}
	}

	return res;
}

int main()
{
	Matrix a(3, 2);
	Matrix b(2, 4);
	a[0][0] = 1;
	a[0][1] = 1;
	a[1][0] = 1;
	a[1][1] = 1;
	b[0][0] = 1;
	b[0][1] = 1;
	b[1][0] = 1;
	b[1][1] = 1;

	a.print();
	b.print();

	std::cout << "____________" << std::endl;

	Matrix c(1, 1);
	c = a * b;
	
	c.print();

	return 0;
}