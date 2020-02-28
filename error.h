//
// Created by irina on 27.02.2020.
//

#ifndef DIFF_SOLVE_ERROR_H
#define DIFF_SOLVE_ERROR_H

#endif //DIFF_SOLVE_ERROR_H
#include "equation.h"

double abs_error(double u, std::vector<double> u0, double h, double T)
{
	std::ofstream fout;
	fout.open("Error_file_ext.txt");
	double q = 0.1;
	fout << "Eiler explicit \n";
	for (int i = 0; i != 4; i++)
	{
		std::vector<double> tmp(eiler_explicit(u0, T, pow(q, i)*h));
		fout << fabs(u - tmp[0]) << '\t';
		if (i != 0)
		{
			std::vector<double> tmp(eiler_explicit(u0, T, pow(q, i)*h));
			double temp = eiler_explicit(u0, T, pow(q, i - 1)*h)[0];
			fout << fabs(u - tmp[0]) / fabs(u - temp) << '\t';
			fout << log(q) / log(fabs(u - tmp[0]) / fabs(u - temp)) << '\t';
		}
		fout << '\n';
	}
	//fout << "Eiler implicit \n";
	//for (int i = 0; i != 3; i++)
	//{
	//	std::vector<double> tmp(eiler_implicit(u0, T, pow(q, i)*h));
	//	fout << norm(u, tmp) << '\t';
	//	if (i != 0)
	//	{
	//		std::vector<double> tmp1(eiler_implicit(u0, T, pow(q, i - 1)*h));
	//		fout << norm(u, tmp) / norm(u, tmp1) << '\t';
	//		fout << log(q) / log(norm(u, tmp) / norm(u, tmp1)) << '\t';
	//	}
	//	fout << '\n';
	//}
	/*
	fout << "Symmetrical scheme \n";
	for (int i = 0; i != 3; i++ )
	{
		std::vector<double> tmp(sym_scheme(u0, T, pow(q,i)*h));
		fout << norm(u, tmp) << '\t';
		if (i != 0)
		{
			fout << norm(u, tmp)/norm(u, sym_scheme(u0, T, pow(q,i-1)*h)) << '\t';
			fout << log(q)/log(norm(u, tmp)/norm(u, sym_scheme(u0, T, pow(q,i-1)*h))) << '\t';
		}
		fout << '\n';
	}*/
	fout << '\n';
	fout << " Runge-Kutta 2 order without Runge rule\n";
	for (int i = 0; i != 4; i++ )
	{
		fout << fabs(u - run_k_2_2(u0, T, pow(q, i)*h, 0)[0]) << '\t';
		if (i != 0)
		{
			double	tmp = run_k_2_2(u0, T, pow(q, i)*h, 0)[0];
			double	temp = run_k_2_2(u0, T, pow(q, i - 1)*h, 0)[0];
			fout << fabs(u - tmp)/fabs(u - temp) << '\t';
			fout << log(q)/log(fabs(u - tmp) / fabs(u - temp)) << '\t';
		}
		fout << '\n';
	}
	fout << '\n';
	fout << " Runge-Kutta 4 order without Runge rule\n";
	for (int i = 0; i != 4; i++ )
	{
		fout << fabs(u - run_k_4_4(u0, T, pow(q, i)*h, 0, 0)[0]) << '\t';
		if (i != 0)
		{
			double	tmp = run_k_4_4(u0, T, pow(q, i)*h, 0, 0)[0];
			double	temp = run_k_4_4(u0, T, pow(q, i - 1)*h, 0, 0)[0];
			fout << fabs(u - tmp)/fabs(u - temp) << '\t';
			fout << log(q)/log(fabs(u - tmp) / fabs(u - temp)) << '\t';
		}
		fout << '\n';
	}
	fout.close();
	fout << '\n';
	fout << " Runge-Kutta 4 order without Runge rule\n";
	for (int i = 0; i != 4; i++)
	{
		fout << fabs(u - run_k_4_4(u0, T, pow(q, i)*h, 0, 0)[0]) << '\t';
		if (i != 0)
		{
			double	tmp = run_k_4_4(u0, T, pow(q, i)*h, 0, 0)[0];
			double	temp = run_k_4_4(u0, T, pow(q, i - 1)*h, 0, 0)[0];
			fout << fabs(u - tmp) / fabs(u - temp) << '\t';
			fout << log(q) / log(fabs(u - tmp) / fabs(u - temp)) << '\t';
		}
		fout << '\n';
	}
	fout << "Adams\n";
	for (int i = 0; i != 4; i++)
	{
		fout << fabs(u - Adams(u0, T, pow(q, i)*h)[0]) << '\t';
		if (i != 0)
		{
			double	tmp = Adams(u0, T, pow(q, i)*h)[0];
			double	temp = Adams(u0, T, pow(q, i - 1)*h)[0];
			fout << fabs(u - tmp) / fabs(u - temp) << '\t';
			fout << log(q) / log(fabs(u - tmp) / fabs(u - temp)) << '\t';
		}
		fout << '\n';
	}
	fout.close();
	return(0);
}