//
// Created by irina on 27.02.2020.
//

#ifndef DIFF_SOLVE_ERROR_H
#define DIFF_SOLVE_ERROR_H

#endif //DIFF_SOLVE_ERROR_H
#include "equation.h"

double abs_error(double u, std::vector<double> u0, double h, double T, int step)
{
	std::ofstream fout;
	double	temp;

	fout.open("Error_file_ext.txt");
	double q = 0.1;
	fout << "Eiler explicit \n";
	for (int i = 0; i != 4; i++)
	{
		fout << pow(q, i) * h << '\t';
		std::vector<double> tmp(eiler_explicit(u0, T, pow(q, i)*h, step * pow(10, i)));
		fout << fabs(u - tmp[0]) << '\t';
		if (i != 0)
		{
			fout << fabs(u - tmp[0]) / fabs(u - temp) << '\t';
			fout << log(fabs(u - tmp[0]) / fabs(u - temp)) / log(q) << '\t';
		}
		temp = tmp[0];
		fout << '\n';
	}
	fout << '\n';

	fout << "Eiler implicit \n";
	for (int i = 0; i != 4; i++)
	{
		fout << pow(q, i) * h << '\t';
		std::vector<double> tmp(eiler_implicit(u0, T, pow(q, i) * h, step * pow(10, i)));
		fout << fabs(u - tmp[0]) << '\t';
		if (i != 0)
		{
			fout << fabs(u - tmp[0]) / fabs(u - temp) << '\t';
			fout << log(fabs(u - tmp[0]) / fabs(u - temp)) / log(q) << '\t';
		}
		temp = tmp[0];
		fout << '\n';
	}
	fout << '\n';
	
	fout << "Symmetrical scheme \n";
	for (int i = 0; i != 4; i++ )
	{
		std::vector<double> tmp(sym_scheme(u0, T, pow(q, i) * h, step * pow(10, i)));
		fout << fabs(u - tmp[0]) << '\t';
		if (i != 0)
		{
			fout << fabs(u - tmp[0]) / fabs(u - temp) << '\t';
			fout << log(fabs(u - tmp[0]) / fabs(u - temp)) / log(q) << '\t';
		}
		temp = tmp[0];
		fout << '\n';
	}
	fout << '\n';

	fout << " Runge-Kutta 2 order\n";
	for (int i = 0; i != 4; i++)
	{
		fout << pow(q, i) * h << '\t';
		double	tmp = run_k_2_2(u0, T, pow(q, i)*h, step * pow(10, i))[0];
		fout << fabs(u - tmp) << '\t';
		if (i != 0)
		{
			fout << fabs(u - tmp) / fabs(u - temp) << '\t';
			fout << log(fabs(u - tmp) / fabs(u - temp)) / log(q) << '\t';
		}
		temp = tmp;
		fout << '\n';
	}
	fout << '\n';

	fout << " Runge-Kutta 4 order\n";
	for (int i = 0; i != 4; i++)
	{
		fout << pow(q, i) * h << '\t';
		double	tmp = run_k_4_4(u0, T, pow(q, i)*h, 0, step * pow(10, i))[0];
		fout << fabs(u - tmp) << '\t';
		if (i != 0)
		{
			fout << fabs(u - tmp) / fabs(u - temp) << '\t';
			fout << log(fabs(u - tmp) / fabs(u - temp)) / log(q) << '\t';
		}
		temp = tmp;
		fout << '\n';
	}
	fout << '\n';

	fout << "Adams\n";
	for (int i = 0; i != 4; i++)
	{
		fout << pow(q, i) * h << '\t';
		double	tmp = Adams(u0, T, pow(q, i)*h, step * pow(10, i))[0];
		fout << fabs(u - tmp) << '\t';
		if (i != 0)
		{
			fout << fabs(u - tmp) / fabs(u - temp) << '\t';
			fout << log(fabs(u - tmp) / fabs(u - temp)) / log(q) << '\t';
		}
		temp = tmp;
		fout << '\n';
	}
	fout << '\n';

	fout << "Predict-Correction\n";
	for (int i = 0; i != 4; i++)
	{
		fout << pow(q, i) * h << '\t';
		double	tmp = Adams_progn_correct(u0, T, pow(q, i)*h, step * pow(10, i))[0];
		fout << fabs(u - tmp) << '\t';
		if (i != 0)
		{
			fout << fabs(u - tmp) / fabs(u - temp) << '\t';
			fout << log(fabs(u - tmp) / fabs(u - temp)) / log(q) << '\t';
		}
		temp = tmp;
		fout << '\n';
	}
	fout.close();

	return(0);
}

void error_eitken(std::vector<double> u0, double h, double T, int step)
{
	std::ofstream fout;
	double	temp1;
	double	temp2;

	fout.open("Eitken_file_ext.txt");
	double q = 0.1;

	fout << " Explicit Eiler\n";
	for (int i = 0; i != 5; i++)
	{
		fout << pow(q, i) * h << '\t';
		double	tmp = eiler_explicit(u0, T, pow(q, i)*h, step * pow(10, i))[0];
		if (i != 0)
		{
			if (i != 1)
			{
				fout << fabs(tmp - temp1) / fabs(temp2 - temp1) << '\t';
				fout << log(fabs(tmp - temp1) / fabs(temp2 - temp1)) / log(q) << '\t';
			}
			temp2 = temp1;
		}
		temp1 = tmp;
		fout << '\n';
	}
	fout << '\n';

	fout << " Implicit Eiler\n";
	for (int i = 0; i != 5; i++)
	{
		fout << pow(q, i) * h << '\t';
		double	tmp = eiler_implicit(u0, T, pow(q, i)*h, step * pow(10, i))[0];
		if (i != 0)
		{
			if (i != 1)
			{
				fout << fabs(tmp - temp1) / fabs(temp2 - temp1) << '\t';
				fout << log(fabs(tmp - temp1) / fabs(temp2 - temp1)) / log(q) << '\t';
			}
			temp2 = temp1;
		}
		temp1 = tmp;
		fout << '\n';
	}
	fout << '\n';

	fout << " Symetrical scheme\n";
	for (int i = 0; i != 5; i++)
	{
		fout << pow(q, i) * h << '\t';
		double	tmp = sym_scheme(u0, T, pow(q, i)*h, step * pow(10, i))[0];
		if (i != 0)
		{
			if (i != 1)
			{
				fout << fabs(tmp - temp1) / fabs(temp2 - temp1) << '\t';
				fout << log(fabs(tmp - temp1) / fabs(temp2 - temp1)) / log(q) << '\t';
			}
			temp2 = temp1;
		}
		temp1 = tmp;
		fout << '\n';
	}
	fout << '\n';

	fout << " Runge-Kutta 2 order\n";
	for (int i = 0; i != 5; i++)
	{
		fout << pow(q, i) * h << '\t';
		double	tmp = run_k_2_2(u0, T, pow(q, i)*h, step * pow(10, i))[0];
		if (i != 0)
		{
			if (i != 1)
			{
				fout << fabs(tmp - temp1) / fabs(temp2 - temp1) << '\t';
				fout << log(fabs(tmp - temp1) / fabs(temp2 - temp1)) / log(q) << '\t';
			}
			temp2 = temp1;
		}
		temp1 = tmp;
		fout << '\n';
	}
	fout << '\n';

	fout << " Runge-Kutta 4 order\n";
	for (int i = 0; i != 5; i++)
	{
		fout << pow(q, i) * h << '\t';
		double	tmp = run_k_4_4(u0, T, pow(q, i)*h, 0, step * pow(10, i))[0];
		if (i != 0)
		{
			if (i != 1)
			{
				fout << fabs(tmp - temp1) / fabs(temp2 - temp1) << '\t';
				fout << log(fabs(tmp - temp1) / fabs(temp2 - temp1)) / log(q) << '\t';
			}
			temp2 = temp1;
		}
		temp1 = tmp;
		fout << '\n';
	}
	fout << '\n';
	
	fout << " Adams\n";
	for (int i = 0; i != 5; i++)
	{
		fout << pow(q, i) * h << '\t';
		double	tmp = Adams(u0, T, pow(q, i)*h, step * pow(10, i))[0];
		if (i != 0)
		{
			if (i != 1)
			{
				fout << fabs(tmp - temp1) / fabs(temp2 - temp1) << '\t';
				fout << log(fabs(tmp - temp1) / fabs(temp2 - temp1)) / log(q) << '\t';
			}
			temp2 = temp1;
		}
		temp1 = tmp;
		fout << '\n';
	}
	fout << '\n';
	
	fout << " Predixt-Correct\n";
	for (int i = 0; i != 5; i++)
	{
		fout << pow(q, i) * h << '\t';
		double	tmp = Adams_progn_correct(u0, T, pow(q, i)*h, step * pow(10, i))[0];
		if (i != 0)
		{
			if (i != 1)
			{
				fout << fabs(tmp - temp1) / fabs(temp2 - temp1) << '\t';
				fout << log(fabs(tmp - temp1) / fabs(temp2 - temp1)) / log(q) << '\t';
			}
			temp2 = temp1;
		}
		temp1 = tmp;
		fout << '\n';
	}
	fout << '\n';
	fout.close();
}