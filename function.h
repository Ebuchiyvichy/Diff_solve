//
// Created by irina on 17.02.2020.
//

#ifndef DIFF_SOLVE_FUNCTION_H
#define DIFF_SOLVE_FUNCTION_H

#endif //DIFF_SOLVE_FUNCTION_H

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
    std::vector<double> u(2);
    u[0] = 2 * x[0] + x[1]*x[1] - 1;
    u[1] = 6 * x[0] - x[1]*x[1] +1;
    return u;
}

std::vector<double> test2 (std::vector<double> x)
{
    std::vector<double> u(2);
    u[0] = 1 - x[0]*x[0] - x[1]*x[1];
    u[1] = 2* x[0];
    return u;
}