//
// Created by irina on 17.02.2020.
//

#ifndef DIFF_SOLVE_NEWTON_H
#define DIFF_SOLVE_NEWTON_H

#endif //DIFF_SOLVE_NEWTON_H
#include "MatrixClass.h"
double	D(std::vector<double> (*func)(std::vector<double>), std::vector<double> x, int n, int m)
{
    std::vector<double>	tmp(x);

    tmp[m] = x[m] + EPS;
    return (func(tmp)[n] - func(x)[n]) / EPS;
}

double	D_cen(std::vector<double> (*func)(std::vector<double>), std::vector<double> x, int n, int m)
{
    std::vector<double>	tmp1(x);
    std::vector<double>	tmp2(x);

    tmp1[m] = x[m] + EPS;
    tmp2[m] = x[m] - EPS;
    return (func(tmp1)[n] - func(tmp2)[n]) / (2 * EPS);
}

Matrix	Jacoby_matr(std::vector<double> (*func)(std::vector<double>), std::vector<double> x)
{
    Matrix Jac(dim);

    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            Jac.value[i][j] = D(func, x, i, j);
    return Jac;
}

std::vector<double>	Newton(std::vector<double> (*func)(std::vector<double>), std::vector<double> x)
{
    std::vector<double>	xk(dim);
    std::vector<double>	a(dim);
    std::vector<double>	b(dim);
    Matrix	J_(dim);
    Matrix	R(dim);
    Matrix	T(dim);
    int		i = 1;

    boaders(func, &a[0], &b[0]);
    for (int i = 1; i < dim; i++)
    {
        a[i] = a[0];
        b[i] = b[0];
    }
    Matrix	J = Jacoby_matr(func, x);
    R = J;
    T.onebyone();
    T.QR_find_x(R);
    J_.inverse_matrix(R, T);
    do
    {
        i++;
        xk = x;
        if (norm (xk, b) < EPS || norm(xk, a) < EPS)
        {
            std::cout << "You are out of diap!" << std::endl;
            return (xk);
        }
        J = Jacoby_matr(func, xk);
        R = J;
        T.onebyone();
        T.QR_find_x(R);
        J_.inverse_matrix(R, T);
        x = xk - func(xk) * J_;
    } while (norm(xk, x) > EPS);
    std::cout << "Nbr of iteration in newton: " << i << std::endl;
    return x;
}