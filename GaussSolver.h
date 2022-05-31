#pragma once


class GaussSolver
{
public:
	GaussSolver();

	std::vector <Vector> solve(const Matrix& A, const Vector& b);

	std::string Test1();
	std::string Test2();
	std::string Test3();
	std::string Test4();

};