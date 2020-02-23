#pragma once
#include "Runge_Kut.h"

void	run_k_4_4_for_one(std::vector<double> *u0, double T, double h)
{
	std::vector<double> k_n1(dim);
	std::vector<double> k_n2(dim);
	std::vector<double> k_n3(dim);
	std::vector<double> k_n4(dim);

		k_n1 = func(*u0);
		k_n2 = func(*u0 + h / 2 * k_n1);
		k_n3 = func(*u0 + h / 2 * k_n2);
		k_n4 = func(*u0 + h * k_n3);
		*u0 = *u0 + h * (1.0 / 6.0) * (k_n1 + 2 * k_n2 + 2 * k_n3 + k_n4);
}

void	Adams(std::vector<double> u0, double T, double h)
{
	std::vector<double> y_n(dim);
	std::vector<double> y_n1(dim);
	std::vector<double> y_n2(dim);
	std::vector<double> y_n3(dim);
	std::vector<double> progn(dim);
	std::vector<double> correct(dim);

	std::ofstream fout;

	fout.open("Adams.txt");
	y_n3 = u0;
	fout << 0 << '\t';
	for (int j = 0; j < dim; j++)
		fout << y_n3[j] << '\t';
	fout << std::endl;
	run_k_4_4_for_one(&y_n3, T, h);
	fout << h << '\t';
	for (int j = 0; j < dim; j++)
		fout << y_n3[j] << '\t';
	fout << std::endl;
	y_n2 = y_n3;
	run_k_4_4_for_one(&y_n2, T, h);
	fout << 2 * h << '\t';
	for (int j = 0; j < dim; j++)
		fout << y_n3[j] << '\t';
	fout << std::endl;
	y_n1 = y_n2;
	run_k_4_4_for_one(&y_n1, T, h);
	fout << 3 * h << '\t';
	for (int j = 0; j < dim; j++)
		fout << y_n3[j] << '\t';
	fout << std::endl;
	y_n = y_n1;
	run_k_4_4_for_one(&y_n, T, h);
	fout << 4 * h << '\t';
	for (int j = 0; j < dim; j++)
		fout << y_n3[j] << '\t';
	fout << std::endl;

	for (double i = 5 * h; i <= T; i += h)
	{
		progn = y_n + h / 24 * (55 * func(y_n) - 59 * func(y_n1) + 37 * func(y_n2) - 9 * func(y_n3));
		correct = y_n + h / 24 * (9 * func(progn) + 19 * func(y_n) - 5 * func(y_n1) + func(y_n2));
		y_n3 = y_n2;
		y_n2 = y_n1;
		y_n1 = y_n;
		y_n = correct;
		fout << i << '\t';
		for (int j = 0; j < dim; j++)
			fout << y_n[j] << '\t';
		fout << std::endl;
	}
	fout.close();
	std::cout << "Adams has done." << std::endl;
}