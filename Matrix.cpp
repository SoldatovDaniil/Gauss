#include "StartIncluder.h"


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

Vector Matrix::operator[](int a) const
{
	return data[a];
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
	return res;
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
		std::cout << data[i];
	}
}

bool operator==(const Matrix& m1, const Matrix& m2)
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


bool operator!=(const Matrix& m1, const Matrix& m2)
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

int Matrix::getM()
{
	return m;
}

int Matrix::getN()
{
	return n;
}
void Matrix::swap(int row1, int row2, int N)
{
	int temp; 

	for (int i = 0; i < N; i++)
	{
		temp = data[row1][i];
		data[row1][i] = data[row2][i];
		data[row2][i] = temp;
	}
}

Matrix Matrix::trans()
{
	Matrix tmp(n, m);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			tmp[j][i] = data[i][j];
		}
	}

	return tmp;
}

void Matrix::sort(int col)
{
	double tmp, max = 0;
	int index = col;

	for (int i = col; i < m; i++)
	{
		if (abs(data[i][col]) > max)
		{
			max = abs(data[i][col]);
			index = i;
		}
	}

	for (int j = 0; j < n; j++)
	{
		tmp = data[index][j];
		data[index][j] = data[col][j];
		data[col][j] = tmp;
	}
}

void Matrix::traengl()
{
	double  tmp, max, temp;
	int k, index;

	for (int i = 0; i < m; i++)
	{
		(*this).sort(i);
		tmp = data[i][i];

		for (int j = m; j >= i; j--)
		{
			data[i][j] /= tmp;
		}
		for (int j = i + 1; j < m; j++)
		{
			tmp = data[j][i];
			for (k = m; k >= i; k--)
			{
				data[j][k] -= tmp * data[i][k];
			}
		}
	}
}


int Matrix::rank()
{
	Matrix mat(m, n);

	if (m >= n)
	{
		mat = *this;
	}
	else
	{
		mat = (*this).trans();
	}

	int rank1 = mat.getN();

	for (int i = 0; i < rank1; i++)
	{
		if (mat[i][i] != 0)
		{
			for (int j = 0; j < m; j++)
			{
				if (i != j)
				{
					double z = mat[j][i] / mat[i][i];

					for (int k = 0; k < rank1; k++)
					{
						mat[j][k] -= z * mat[i][k];
					}
				}
			}
		}
		else
		{
			int flag = 1; 

			for (int k = i + 1; k < m; k++)
			{
				if (mat[k][i] != 0)
				{
					mat.swap(i, k, rank1);
					flag = 0;
					break;
				}
			}

			if (flag != 0)
			{
				rank1--;

				for (int k = 0; k < m; k++)
				{
					mat[k][i] = mat[k][rank1];
				}
			}
			i--;
		}
	}

	return rank1;
}