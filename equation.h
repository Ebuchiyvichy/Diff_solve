#ifndef DIFF_SOLVE_EQUATION_H
#define DIFF_SOLVE_EQUATION_H

#endif //DIFF_SOLVE_EQUATION_H

#include "newton.h"

void	test_init(int TEST, std::vector<double>* u0, double *T)
{
	switch (TEST) {
	case 0:
		u0[0][0] = 1.;
		u0[0][1] = 0.;
		func = &spring;
		*T = 1;
		break;

	case 1:
		u0[0][0] = 2.;
		u0[0][1] = 0.;
		func = &test1;
		*T = 1;
		break;

	case 2:
		u0[0][0] = 1;
		u0[0][1] = 0;
		func = &test2;
		*T = 0.7;
		break;

	case 3:
		u0[0][0] = 1;
		u0[0][1] = 0;
		u0[0][2] = 0;
		func = &test3;
		*T = 35;
		break;
	case 4: 
		u0[0][0] = 0.1;
		u0[0][1] = 0.1;
		func = &test4;
		*T = 200;
		break;
	case 42:
		u0[0][0] = 0.1;
		u0[0][1] = 0.1;
		func = &test42;
		*T = 50;
		break;
	case 46:
		u0[0][0] = 1.0;
		u0[0][1] = 2.0;
		func = &test46;
		*T = 50;
		break;
	default:
		break;
	}
}

std::vector<double>	eiler_explicit(std::vector<double> u0, double T, double h, int step)
{
	std::ofstream fout;
	fout.open("Explicit_eiler.txt");
	int		k = 0;

	for (double i = 0; i <= T; i = i + h)
	{
		fout << i << '\t';
		k++;
		for (int j = 0; j < dim; j++)
			fout << u0[j] << '\t';
		fout << std::endl;
		u0 = u0 + h * (func(u0, i));
		if (k == step)
			return u0;
	}
	fout.close();
	std::cout << "Explicit Eiler has done." << std::endl;
    return u0;
}

std::vector<double>	eiler_implicit(std::vector<double> u0, double T, double h, int step)
{
	std::vector<double> yk(u0);
	int					k = 0;

	std::ofstream fout;
	fout.open("Implicit_eiler.txt");
	for (double i = 0; i <= T; i = i + h)
	{
		k++;
		fout << i << '\t';
		for (int j = 0; j < dim; j++)
			fout << u0[j] << '\t';
		fout << std::endl;
		yk = Newton(yk, u0, h);
		u0 = yk;
		if (k == step)
			return u0;
	}
	fout.close();
	std::cout << "Implicit Eiler has done." << std::endl;
    return u0;
}

std::vector<double>	sym_scheme(std::vector<double> u0, double T, double h, int step)
{
	std::vector<double> yk(u0);
	std::ofstream		fout;
	int					k = 0;

	fout.open("Sym_scheme.txt");
	for (double i = 0; i <= T; i = i + h)
	{
		k++;
		fout << i << '\t';
		for (int j = 0; j < dim; j++)
			fout << u0[j] << '\t';
		fout << std::endl;
		Newton_sym(&yk, u0, h);
		u0 = yk;
		if (k == step)
			return (u0);
	}
	fout.close();
	std::cout << "Symmetrical scheme has done." << std::endl;
    return u0;
}
