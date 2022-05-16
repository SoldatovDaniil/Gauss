#include "StartIncluder.h"


int main()
{
	int m, n, len = 0;
	double inpt = 0;

	std::cout << "Input your system A*x=b (First input size A) \nm = ";
	std::cin >> m;
	std::cout << "n = ";
	std::cin >> n;
	std::cout << "Input A" << std::endl;

	Matrix A(m, n);

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cin >> inpt;
			A[i][j] = inpt;
		}
	}

	std::cout << "\nMatrix A:\n" << std::endl;
	A.print();

	std::cout << "\nInput size b \nm = ";
	std::cin >> len;
	std::cout << "Input b" << std::endl;

	Vector b(len);

	for (int i = 0; i < len; i++)
	{
		std::cin >> inpt;
		b[i] = inpt;
	}

	std::cout << "\nb:" << std::endl;
	b.print();


	GaussSolver System1;
	std::vector <Vector> res = System1.solve(A, b);


	if (res.empty())
	{
		std::cout << "\nNo one system's solutions " << std::endl;
	}
	else
	{
		std::cout << "\nSystem's solution: " << std::endl;
		for (int i = 0; i < n; i++)
		{
			std::cout << "x" << i + 1 << " = " << res[0][i] << "  ";
		}
	}
	std::cout << '\n' << System1.Test1() << std::endl;
	std::cout << System1.Test2() << std::endl;
	std::cout << System1.Test3() << std::endl;


 	return 0;
}