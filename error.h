//
// Created by irina on 27.02.2020.
//

#ifndef DIFF_SOLVE_ERROR_H
#define DIFF_SOLVE_ERROR_H

#endif //DIFF_SOLVE_ERROR_H
#include "equation.h"

double abs_error(std::vector<double> u, std::vector<double> u0, double h, double T)
{
    std::fstream fout;
    fout.open("Error_file_ext.txt");
    double q = 0.1;
    fout << "Eiler explicit \n";
    for (int i = 0; i != 5; i++ )
    {
        fout << norm(u, eiler_explicit(u0, T, pow(q,i)*h)) << '\t';
        if (i != 1)
        {
            fout << norm(u, eiler_explicit(u0, T, pow(q,i)*h))/norm(u, eiler_explicit(u0, T, pow(q,i-1)*h)) << '\t';
            fout << log(q)/log(norm(u, eiler_explicit(u0, T, pow(q,i)*h))/norm(u, eiler_explicit(u0, T, pow(q,i-1)*h))) << '\t';
        }
        fout << '\n';
    }
    fout << "Eiler implicit \n";
    for (int i = 0; i != 5; i++ )
    {
        fout << norm(u, eiler_implicit(u0, T, pow(q,i)*h)) << '\t';
        if (i != 1)
        {
            fout << norm(u, eiler_implicit(u0, T, pow(q,i)*h))/norm(u, eiler_implicit(u0, T, pow(q,i-1)*h)) << '\t';
            fout << log(q)/log(norm(u, eiler_implicit(u0, T, pow(q,i)*h))/norm(u, eiler_implicit(u0, T, pow(q,i-1)*h))) << '\t';
        }
        fout << '\n';
    }
    fout << "Symmetrical scheme \n";
    for (int i = 0; i != 5; i++ )
    {
        fout << norm(u, sym_scheme(u0, T, pow(q,i)*h)) << '\t';
        if (i != 1)
        {
            fout << norm(u, sym_scheme(u0, T, pow(q,i)*h))/norm(u, sym_scheme(u0, T, pow(q,i-1)*h)) << '\t';
            fout << log(q)/log(norm(u, sym_scheme(u0, T, pow(q,i)*h))/norm(u, sym_scheme(u0, T, pow(q,i-1)*h))) << '\t';
        }
        fout << '\n';
    }
    /*
    fout << " Runge-Kutta 2 order without Runge rule\n";
    for (int i = 0; i != 5; i++ )
    {
        fout << norm(u, run_k_2_2(u0, T, pow(q,i)*h, 0)) << '\t';
        if (i != 1)
        {
            fout << norm(u, run_k_2_2(u0, T, pow(q,i)*h, 0))/norm(u, run_k_2_2(u0, T, pow(q,i-1)*h, 0)) << '\t';
            fout << log(q)/log(norm(u, run_k_2_2(u0, T, pow(q,i)*h, 0))/norm(u, run_k_2_2(u0, T, pow(q,i-1)*h, 0))) << '\t';
        }
        fout << '\n';
    }
    fout << " Runge-Kutta 2 order with Runge rule\n";
    for (int i = 0; i != 5; i++ )
    {
        fout << norm(u, run_k_2_2(u0, T, pow(q,i)*h, 1)) << '\t';
        if (i != 1)
        {
            fout << norm(u, run_k_2_2(u0, T, pow(q,i)*h, 1))/norm(u, run_k_2_2(u0, T, pow(q,i-1)*h, 1)) << '\t';
            fout << log(q)/log(norm(u, run_k_2_2(u0, T, pow(q,i)*h, 1))/norm(u, run_k_2_2(u0, T, pow(q,i-1)*h, 1))) << '\t'
        }
        fout << '\n';
    }
     */

}
