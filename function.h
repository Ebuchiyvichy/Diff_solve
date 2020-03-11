//
// Created by irina on 17.02.2020.
//

#ifndef DIFF_SOLVE_FUNCTION_H
#define DIFF_SOLVE_FUNCTION_H

#endif //DIFF_SOLVE_FUNCTION_H

#include "MatrixClass.h"
std::vector<double> f_new(std::vector<double> yn_1, std::vector<double> u0, double h)
{
    std::vector<double> y(dim);
    y = yn_1 - u0 - h * func(yn_1) ;
    return y;
}

std::vector<double> f_new_sym(std::vector<double> yn_1, std::vector<double> u0, double h)
{
	std::vector<double> y(dim);
	y = yn_1 - u0 - h / 2 * (func(yn_1) + func(u0));
	return y;
}

double	check_func(double x)
{
	return cos(x * sqrt(20 / 0.03));
}

double	check_func_dif(double x)
{
	return -sin(x * sqrt(20 / 0.3)) * sqrt(20 / 0.3);
}

static std::vector<double> spring(std::vector<double> x)
{
    std::vector<double> u(2);
    double k = 20; double m = 0.03;

    u[1] = (-1) * k / m * x[0];
    u[0] = x[1];
    return u;
}

static std::vector<double> test1(std::vector<double> x)
{
    std::vector<double> u(dim);

    u[0] = 2 * x[0] + x[1]*x[1] - 1;
    u[1] = 6 * x[0] - x[1]*x[1] + 1;
    return u;
}

static std::vector<double> test2(std::vector<double> x)
{
    std::vector<double> u(dim);

    u[0] = 1 - x[0]*x[0] - x[1]*x[1];
    u[1] = 2 * x[0];
    return u;
}

static std::vector<double> test3(std::vector<double> x)
{
	std::vector<double> u(dim);

	u[0] = 10 * (x[1] - x[0]);
	u[1] = x[0] * (28 - x[2]) - x[1];
	u[2] = x[0] * x[1] - 8 / 3 * x[2];
	return u;
}

static std::vector<double> test4(std::vector<double> x)
{
	std::vector<double> u(dim);
	double				d = 0.3;
	double				w = 1.0;
	double				a = 1.0;

	u[0] = x[1];
	u[1] = 2 * d * x[1] - 2 * d * a * x[1] * x[0] * x[0] + w * w * x[0];
	return u;
}