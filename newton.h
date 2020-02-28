#ifndef DIFF_SOLVE_NEWTON_H
#define DIFF_SOLVE_NEWTON_H

#endif //DIFF_SOLVE_NEWTON_H
#include "Adams.h"

double	D (std::vector<double> x, int n, int m)
{
    std::vector<double>	tmp(x);

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

void Newton(std::vector<double> *x, std::vector<double> u0, double h)
{
    std::vector<double>	xk(*x);
    Matrix	J_(dim);
    Matrix  J(dim);
    Matrix	R(dim);
    Matrix	T(dim);
	double	tmp;

    do
    {
        xk = *x;
        J = Jacoby_matr(xk);
        R = J;
        T.onebyone();
        T.QR_find_x(R);
        J_.inverse_matrix(R, T);
        *x = xk - f_new(xk, u0, h) * J_;
		//tmp = J.value[0][0] * J.value[1][1] - J.value[0][1] * J.value[1][0];
		//J_.value[0][0] = J.value[1][1] / tmp;
		//J_.value[0][1] = -J.value[0][1] / tmp;
		//J_.value[1][0] = -J.value[1][0] / tmp;
		//J_.value[1][1] = J.value[0][0] / tmp;
		*x = xk - f_new_sym(xk, u0, h) * J_;

//		std::cout << "xk = " << xk[0] << "; " << xk[1] << std::endl;
//		std::cout << "f_new = " << (f_new(xk, u0, h))[0] << "; " << (f_new(xk, u0, h))[1] << std::endl;
//		std::cout << "x = " << (*x)[0] << "; " << (*x)[1] << std::endl;	
	} while (norm(xk, *x) > EPS);
}

void Newton_sym(std::vector<double> *x, std::vector<double> u0, double h)
{
	std::vector<double>	xk(*x);
	Matrix	J_(dim);
	Matrix  J(dim);
	Matrix	R(dim);
	Matrix	T(dim);
	double	tmp;

	do
	{
		xk = *x;
		J = Jacoby_matr(xk);
	//	R = J;
	//	T.onebyone();
	//	T.QR_find_x(R);
	//J_.inverse_matrix(R, T);
		tmp = J.value[0][0] * J.value[1][1] - J.value[0][1] * J.value[1][0];
		J_.value[0][0] = J.value[1][1] / tmp;
		J_.value[0][1] = -J.value[0][1] / tmp;
		J_.value[1][0] = -J.value[1][0] / tmp;
		J_.value[1][1] = J.value[0][0] / tmp;
		*x = xk - f_new_sym(xk, u0, h) * J_;

		//		std::cout << "xk = " << xk[0] << "; " << xk[1] << std::endl;
		//		std::cout << "f_new = " << (f_new(xk, u0, h))[0] << "; " << (f_new(xk, u0, h))[1] << std::endl;
		//		std::cout << "x = " << (*x)[0] << "; " << (*x)[1] << std::endl;	
	} while (norm(xk, *x) > EPS);
}