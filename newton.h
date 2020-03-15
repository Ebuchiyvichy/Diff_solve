#ifndef DIFF_SOLVE_NEWTON_H
#define DIFF_SOLVE_NEWTON_H

#endif //DIFF_SOLVE_NEWTON_H
#include "Adams.h"

double	D(std::vector<double> x, int n, int m, std::vector<double> u0, double h, int flag)
{
    std::vector<double>	tmp(x);

    tmp[m] = x[m] + EPS;
	if (flag == 0)
		return (f_new(tmp, u0, h)[n] - f_new(x, u0, h)[n]) / EPS;
	else
		return (f_new_sym(tmp, u0, h)[n] - f_new_sym(x, u0, h)[n]) / EPS;
}

Matrix	Jacoby_matr(std::vector<double> x, std::vector<double> u0, double h, int flag)
{
    Matrix Jac(dim);

    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            Jac.value[i][j] = D(x, i, j, u0, h, flag);
    return Jac;
}

std::vector<double> Newton(std::vector<double> x, std::vector<double> u0, double h)
{
    std::vector<double>	xk(x);
    Matrix	J_(dim);
    Matrix  J(dim);
    Matrix	R(dim);
    Matrix	T(dim);

    do
    {
        xk = x;
        J = Jacoby_matr(xk, u0, h, 0);
        R = J;
        T.onebyone();
        T.QR_find_x(R);
        J_.inverse_matrix(R, T);
		x = xk - J_ * f_new(xk, u0, h);
	} while (norm(xk, x) > EPS);
	return (x);
}

void Newton_sym(std::vector<double> *x, std::vector<double> u0, double h)
{
	std::vector<double>	xk(*x);
	Matrix	J_(dim);
	Matrix  J(dim);
	Matrix	R(dim);
	Matrix	T(dim);

	do
	{
		xk = *x;
		J = Jacoby_matr(xk, u0, h, 1);
			R = J;
			T.onebyone();
			T.QR_find_x(R);
		J_.inverse_matrix(R, T);
		*x = xk - J_ * f_new_sym(xk, u0, h);
	} while (norm(xk, *x) > EPS);
}