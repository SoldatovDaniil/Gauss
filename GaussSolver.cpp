#include "StartIncluder.h"


GaussSolver::GaussSolver()
{
}

std::vector <Vector> GaussSolver::solve(const Matrix& A, const Vector& b)
{
    Matrix a = A;
    Vector y = b;
    int n = y.getSize();
    int M = a.getM();
    int N = a.getN();
    std::vector <Vector> res(1, Vector(N));
    std::vector <Vector> res1(0, 0);

    Matrix exMat(M, N + 1);
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            exMat[i][j] = a[i][j];
        }
    }
    for (int k = 0; k < M; k++)
    {
        exMat[k][N] = y[k];
    }

    if (M != n)
    {
        return res1;
    }

    exMat.traengl();

    for (int i = 0; i < M; i++)
    {
        if (exMat[i].check(i))
        {
            return res1;
        }
    }

    std::vector<int> detect(N + 1, -1);
    int countTrue = 0;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (exMat[i][j] != 0)
            {
                detect[j] = i;
                countTrue += 1;
                break;
            }
        }
    }

    if (countTrue == N)
    {
        res[0][M - 1] = exMat[M - 1][M];
        for (int i = M - 2; i >= 0; i--)
        {
            res[0][i] = exMat[i][M];
            for (int j = i + 1; j < M; j++)
                res[0][i] -= exMat[i][j] * res[0][j];
        }
    }

    else
    {
        std::vector<int> ready(N, 0);
        Matrix eq(N, N + 1);
        int countFalse, Col = -1;
        countFalse = N - countTrue;

        for (int i = 0; i < N; i++)
        {
            if (detect[i] == -1)
            {
                eq[i][i] = 1;
            }
        }

        std::vector <Vector> res2(countFalse + 1, Vector(N));

        for (int i = exMat.getM() - 1; i >= 0; i--)
        {
            if (exMat.checkStr(i))
            {   
                for (int j = 0; j < N; j++)
                {
                    if ((detect[j] != -1) && (exMat[i][j] != 0))
                    {
                        Col = j;
                        break;
                    }
                }

                if ((ready[Col] == 1) || (Col == -1))
                {
                    continue;
                }

                for (int j = Col + 1; j < N + 1; j++)
                {
                    if ((detect[j] != -1))
                    {
                        for (int k = 0; k < N + 1; k++)
                        {
                            eq[Col][k] += (-1) * ((exMat[i][j]) * (eq[j][k] / exMat[i][Col]));
                        }
                    }
                    else
                    {
                        eq[Col][j] += (-1) * (exMat[i][j] / exMat[i][Col]);
                    }
                }

                ready[Col] = 1;
            } 
            else
            {
                continue;
            }
        }

        for (int i = 0; i < res2.size(); i++)
        {
            res2[0][i] += (-1) * eq[i][N];
        }

        for (int i = 1; i < countFalse + 1; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (detect[j] == -1)
                {
                    for (int k = 0; k < N; k++)
                    {
                        res2[i][k] = eq[k][j];
                    }
                }
                else
                {
                    continue;
                }
            }
        }

        return res2;
    }

    return res;
}

std::string GaussSolver::Test1() 
{
    GaussSolver TestSystem;
    Matrix test(3, 3);
    Vector t(3);
    double eps = 0.0001;
    std::vector <Vector> answer(1, Vector(3));
    std::vector <Vector> answer1(1, Vector(3));
    test[0][0] = 2;
    test[0][1] = 1;
    test[0][2] = 1;
    test[1][0] = 1;
    test[1][1] = -1;
    test[1][2] = 0;
    test[2][0] = 3;
    test[2][1] = -1;
    test[2][2] = 2;
    t[0] = 2;
    t[1] = -2;
    t[2] = 2;
    answer[0][0] = -1;
    answer[0][1] = 1;
    answer[0][2] = 3;
    
    answer1 = TestSystem.solve(test, t);

    for (int i = 0; i < 3; i++)
    {
        if (abs(answer[0][i] - answer1[0][i]) > eps)
        {
            return "Test 1 was NOT passed";
        }
    }

    return "Test 1 was passed"; 
}

std::string GaussSolver::Test2()
{
    GaussSolver TestSystem;
    Matrix test(3, 3);
    Vector t(3);
    double eps = 0.0001;
    std::vector <Vector> answer(1, Vector(3));
    std::vector <Vector> answer1(1, Vector(3));
    test[0][0] = 2;
    test[0][1] = 3;
    test[0][2] = -1;
    test[1][0] = 1;
    test[1][1] = -2;
    test[1][2] = 1;
    test[2][0] = 1;
    test[2][1] = 0;
    test[2][2] = 2;
    t[0] = 9;
    t[1] = 3;
    t[2] = 2;
    answer[0][0] = 4;
    answer[0][1] = 0;
    answer[0][2] = -1;

    answer1 = TestSystem.solve(test, t);

    for (int i = 0; i < 3; i++)
    {
        if (abs(answer[0][i] - answer1[0][i]) > eps)
        {
            return "Test 2 was NOT passed";
        }
    }

    return "Test 2 was passed";
}

std::string GaussSolver::Test3()
{
    GaussSolver TestSystem;
    Matrix test(4, 4);
    Vector t(4);
    double eps = 0.001;
    std::vector <Vector> answer(4, Vector(4));
    std::vector <Vector> answer1(4, Vector(4));

    test[0][0] = 1;
    test[0][1] = 2;
    test[0][2] = 3;
    test[0][3] = -2;
    test[1][0] = 2;
    test[1][1] = -1;
    test[1][2] = -2;
    test[1][3] = -3;
    test[2][0] = 3;
    test[2][1] = 2;
    test[2][2] = -1;
    test[2][3] = 2;
    test[3][0] = 2;
    test[3][1] = -3;
    test[3][2] = 2;
    test[3][3] = 1;

    t[0] = 1;
    t[1] = 2;
    t[2] = -5;
    t[3] = 11;

    answer[0][0] =  (2./3.);
    answer[0][1] = (-43./18.);
    answer[0][2] =  (26./18.);
    answer[0][3] = (-7./18.);

    answer1 = TestSystem.solve(test, t);

    for (int i = 0; i < 4; i++)
    {
        if (abs(answer[0][i] - answer1[0][i]) > eps)
        {
            return "\n Test 3 was NOT passed";
        }
    }

    return "Test 3 was passed";
}

std::string GaussSolver::Test4()
{
    GaussSolver TestSystem;
    Matrix test(3, 3);
    Vector t(3);
    double eps = 0.001;
    std::vector <Vector> answer(2, Vector(3));
    std::vector <Vector> answer1(2, (Vector(3)));

    test[0][0] = 3;
    test[0][1] = 1;
    test[0][2] = 4;
    test[1][0] = -4;
    test[1][1] = 2;
    test[1][2] = 1;
    test[2][0] = -5;
    test[2][1] = 5;
    test[2][2] = 6;
    t[0] = 43;
    t[1] = 3;
    t[2] = 49;
    answer[0][0] = 8.3;
    answer[0][1] = 18.1;
    answer[0][2] = 0;
    answer[1][0] = -(0.7);
    answer[1][1] = -(1.9);
    answer[1][2] = 1;

    answer1 = TestSystem.solve(test, t);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (abs(answer[i][j] - answer1[i][j]) > eps)
            {
                return "Test 4 was not passed";
            }
        }
    }

    return "Test 4 was passed";
}