//
// Created by irina on 12.02.2020.
//

#ifndef DIFF_SOLVE_EQUATION_H
#define DIFF_SOLVE_EQUATION_H

#endif //DIFF_SOLVE_EQUATION_H

#include "function.h"

void test_init(int TEST, std::vector<double>* u0, double *T, std::vector<double> (*func)(std::vector<double>))
{
    switch (TEST) {
        case 0:
            u0[0][0] = 1.;
            u0[1][0] = 0.;
            func = spring;
            break;

        case 1:
            u0[0][0] = 2.;
            u0[1][0] = 0.;
            func = test1;
            break;

        case 2:
            u0[0][0] = 1;
            u0[1][0] = 0;
            func = test2;
            break;

        case 3: {
        }
        default:
            break;
    }
}

void eiler_explicit(std::vector<double> u0, double T, double h, std::vector<double> (*func)(std::vector<double>))
{
    std::ofstream fout;
    fout.open("Explicit_eiler.txt");
    for (int i = 0; i <= T; i += i+h )
    {
        fout << i << '\t' << u0[0] <<'\t' << u0[1]<< std::endl;
        u0 = u0 + h * func(u0);
    }
    fout.close();
}
void eiler_implicit(std::vector<double> y0, double T, int h, double (*func)(std::vector<double>))
{
    std::vector<double> y(y0);
    std::ofstream fout;
    fout.open("Implicit_eiler.txt");

    fout.close();

}