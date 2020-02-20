//
// Created by irina on 17.02.2020.
//

#ifndef DIFF_SOLVE_NEWTON_H
#define DIFF_SOLVE_NEWTON_H

#endif //DIFF_SOLVE_NEWTON_H
#include "MatrixClass.h"
double	D (std::vector<double> x, int n, int m)
{
    std::vector<double>	tmp(x);
    std::vector<double> tmp1(dim);

    tmp[m] = x[m] + EPS;
    return (func(tmp)[n] - func(x)[n]) / EPS;
}

double	D_cen(std::vector<double> x, int n, int m)
{
    std::vector<double>	tmp1(x);
    std::vector<double>	tmp2(x);

    tmp1[m] = x[m] + EPS;
    tmp2[m] = x[m] - EPS;
    return (func(tmp1)[n] - func(tmp2)[n]) / (2 * EPS);
}

Matrix	Jacoby_matr(std::vector<double> x)
{
    Matrix Jac(dim);

    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            Jac.value[i][j] = D( x, i, j);
    return Jac;
}

void Newton(std::vector<double> x)
{
    std::vector<double>	xk(x);
    Matrix	J_(dim);
    Matrix  J(dim);
    Matrix	R(dim);
    Matrix	T(dim);
    std::ofstream fout;
    fout.open("Implicit_eiler.txt");
    do
    {
        xk = x;
        J = Jacoby_matr(xk);
        R = J;
        T.onebyone();
        T.QR_find_x(R);
        J_.inverse_matrix(R, T);
        x = xk - func(xk) * J_;
    } while (norm(xk, x) > EPS);
    std::cout << x[0] << '\t';
    fout << x[0] << '\t' << x[1] << std::endl;
    fout.close();
}