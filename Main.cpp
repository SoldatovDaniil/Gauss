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
	else if (res.size() == 1)
	{
		std::cout << "\nSystem's solution: " << std::endl;
		for (int i = 0; i < n; i++)
		{
			std::cout << "x" << i + 1 << " = " << res[0][i] << "  ";
		}
	}
	else if (res.size() >= 1)
	{
		std::vector <int> index(n, -1);
		int oneCount = 0, count = 0;

		for (int i = 0; i < n; i++)
		{
			if (res[0][i] == 0)
			{
				index[i] = i;
				count += 1;
			}
		}

		for (int i = 0; i < n; i++)
		{
			oneCount = 0;
			if (index[i] != -1)
			{
				for (int j = 0; j < res.size(); j++)
				{
					if ((res[j][i] != 1) && (res[j][i] != 0))
					{
						index[i] = -1;
						count -= 1;
						break;
					}
					if (res[j][i] == 1)
					{
						oneCount += 1;
					}
				}
				if (oneCount == 1)
				{
					index[i] = i;
				}
				else
				{
					index[i] = -1;
					count -= 1;
				}
			}
		}

		std::vector <int> ind(count, 0);
		int point = 0;
		for (int i = 0; i < n; i++)
		{
			if (index[i] != -1)
			{
				ind[point] = index[i];
				point++;
			}
		}

		std::cout << "\nSystem's solution: \n [";
		for (int i = 0; i < n; i++)
		{
			std::cout << ' ' << res[0][i];
		}
		std::cout << " ]";

		int p = 0;
		for (int i = 1; i < res.size(); i++)
		{
			std::cout << " + [";
			for (int j = 0; j < n; j++)
			{
				std::cout << " " << res[i][j];
			}
			std::cout << " ] * x" << ind[p] + 1;
			p++;
		}
	}

	std::cout << '\n' << System1.Test1();
	std::cout << '\n' << System1.Test2();
	std::cout << '\n' << System1.Test3();
	std::cout << '\n' << System1.Test4();
 	return 0;
}