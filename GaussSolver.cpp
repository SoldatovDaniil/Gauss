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
    std::vector <Vector> res(1, Vector(n));
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

    int rankA, rankExMat;
    rankA = a.rank();
    rankExMat = exMat.rank();

    if (rankA != rankExMat)
    {
        return res1;
    }

    if ((M != n) || (N > n) || (M < N))
    {
        return res1;
    }
    
    exMat.traengl();
    
    // добавить проверку рангов и два обратных хода (1 при единственном решении, второй при многообразии)
    if (rankA == rankExMat && rankA == M)
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
        // ресайз для вектора res + другой обратный ход с множеством решений
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