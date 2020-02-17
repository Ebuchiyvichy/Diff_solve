//
// Created by irina on 17.02.2020.
//

#ifndef DIFF_SOLVE_FUNCTION_H
#define DIFF_SOLVE_FUNCTION_H

#endif //DIFF_SOLVE_FUNCTION_H

#include "newton.h"

std::vector<double> spring(std::vector<double> x)
{
    std::vector<double> u(2);
    double k = 20; double m = 0.03;
    u[1] = - k / m * x[0];
    u[0] = x[1];
    return u;
}

std::vector<double> test1 (std::vector<double> x)
{
    std::vector<double> u(dim);
    u[0] = 2 * x[0] + x[1]*x[1] - 1;
    u[1] = 6 * x[0] - x[1]*x[1] +1;
    return u;
}

std::vector<double> test2 (std::vector<double> x)
{
    std::vector<double> u(dim);
    u[0] = 1 - x[0]*x[0] - x[1]*x[1];
    u[1] = 2 * x[0];
    return u;
}



//функции для работы с методом Ньютона

std::vector<double>	cpy_vector(std::vector<double> tmp, std::vector<double> x, int size)
{

    for (int i = 0; i < size; i++)
        tmp[i] = x[i];
    return (tmp);
}

std::vector<double>	diff(std::vector<double> a, std::vector<double> b)
{
    std::vector<double>	tmp(dim);

    for (int i = 0; i < dim; i++)
        tmp[i] = a[i] - b[i];
    return (tmp);
}

double	norm(std::vector<double> a, std::vector<double> b)
{
    double	max;
    max = fabs(a[0] - b[0]);
    for (int i = 1; i < dim; i++)
        if (fabs(a[i] - b[i]) > max)
            max = fabs(a[i] - b[i]);
    return max;
}