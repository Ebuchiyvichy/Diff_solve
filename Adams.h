#pragma once
#include "Runge_Kut.h"

void	run_k_4_4_for_one(std::vector<double> *u0, double T, double h, double tau)
{
	std::vector<double> k_n1(dim);
	std::vector<double> k_n2(dim);
	std::vector<double> k_n3(dim);
	std::vector<double> k_n4(dim);

		k_n1 = func(*u0, tau);
		k_n2 = func(*u0 + h / 2 * k_n1, tau);
		k_n3 = func(*u0 + h / 2 * k_n2, tau);
		k_n4 = func(*u0 + h * k_n3, tau);
		*u0 = *u0 + h * (1.0 / 6.0) * (k_n1 + 2 * k_n2 + 2 * k_n3 + k_n4);
}


std::vector<double> progn_correct(std::vector<double>  *y_n, std::vector<double> *y_n1, std::vector<double> *y_n2, std::vector<double> *y_n3, double h, double tau)
{
    std::vector<double> y(dim);
	std::vector<double>	tmp(dim);
    tmp =  *y_n + h / 24.0 * (55.0 * func(*y_n, tau) - 59.0 * func(*y_n1, tau) + 37.0 * func(*y_n2, tau) - 9.0 * func(*y_n3, tau));
    y =  *y_n + h / 24.0 * (9.0 * func(tmp, tau) + 19.0 * func(*y_n, tau) - 5.0 * func(*y_n1, tau) + func(*y_n2, tau));
    *y_n3 = *y_n2;
    *y_n2 = *y_n1;
    *y_n1 = *y_n;
    return y;
}

std::vector<double>	Adams_progn_correct(std::vector<double> u0, double T, double h, int step)
{
	std::vector<double> y_n(dim);
	std::vector<double> y_n1(dim);
	std::vector<double> y_n2(dim);
	std::vector<double> y_n3(dim);
	int					k = 3;

	std::ofstream fout;

	fout.open("Predict_correct.txt");
	y_n3 = u0;
	fout << 0 << '\t';
	for (int j = 0; j < dim; j++)
		fout << y_n3[j] << '\t';
	fout << std::endl;

	/*run_k_4_4_for_one(&y_n3, T, h);
	fout << h << '\t';
	for (int j = 0; j < dim; j++)
		fout << y_n3[j] << '\t';
	fout << std::endl;*/

	y_n2 = y_n3;
	run_k_4_4_for_one(&y_n2, T, h, h);

	fout << h << '\t';
	for (int j = 0; j < dim; j++)
		fout << y_n2[j] << '\t';
	fout << std::endl;

	y_n1 = y_n2;
	run_k_4_4_for_one(&y_n1, T, h, 2 * h);

	fout << 2 * h << '\t';
	for (int j = 0; j < dim; j++)
		fout << y_n1[j] << '\t';
	fout << std::endl;

	y_n = y_n1;
	run_k_4_4_for_one(&y_n, T, h, 3 * h);

	fout << 3 * h << '\t';
	for (int j = 0; j < dim; j++)
		fout << y_n[j] << '\t';
	fout << std::endl;


	for (double i = 4 * h; i <= T; i += h)
	{
		k++;
		y_n = progn_correct(&y_n,&y_n1, &y_n2, &y_n3, h, i);
		fout << i << '\t';
		for (int j = 0; j < dim; j++) { fout << y_n[j] << '\t'; }
		fout << std::endl;
		if (k == step)
			return (y_n);
	}
	fout.close();
	std::cout << "Predict-correction has done." << std::endl;
	return (y_n);
}


std::vector<double> Ad(std::vector<double>  *y_n, std::vector<double> *y_n1, std::vector<double> *y_n2, std::vector<double> *y_n3, double h, double tau)
{
	std::vector<double> y(dim);
	y = *y_n + h / 24.0 * (55.0 * func(*y_n, tau) - 59.0 * func(*y_n1, tau) + 37.0 * func(*y_n2, tau) - 9.0 * func(*y_n3, tau));
	*y_n3 = *y_n2;
	*y_n2 = *y_n1;
	*y_n1 = *y_n;
	return y;
}

std::vector<double>	Adams(std::vector<double> u0, double T, double h, int step)
{
	std::vector<double> y_n(dim);
	std::vector<double> y_n1(dim);
	std::vector<double> y_n2(dim);
	std::vector<double> y_n3(dim);
	int					k = 3;

	std::ofstream fout;

	fout.open("Adams.txt");
	y_n3 = u0;
	fout << 0 << '\t';
	for (int j = 0; j < dim; j++)
		fout << y_n3[j] << '\t';
	fout << std::endl;

	/*run_k_4_4_for_one(&y_n3, T, h);
	fout << h << '\t';
	for (int j = 0; j < dim; j++)
		fout << y_n3[j] << '\t';
	fout << std::endl;*/

	y_n2 = y_n3;
	run_k_4_4_for_one(&y_n2, T, h, h);

	fout << h << '\t';
	for (int j = 0; j < dim; j++)
		fout << y_n2[j] << '\t';
	fout << std::endl;

	y_n1 = y_n2;
	run_k_4_4_for_one(&y_n1, T, h, 2 * h);

	fout << 2 * h << '\t';
	for (int j = 0; j < dim; j++)
		fout << y_n1[j] << '\t';
	fout << std::endl;

	y_n = y_n1;
	run_k_4_4_for_one(&y_n, T, h, 3 * h);

	fout << 3 * h << '\t';
	for (int j = 0; j < dim; j++)
		fout << y_n[j] << '\t';
	fout << std::endl;

	for (double i = 4 * h; i <= T; i += h)
	{
		k++;
		y_n = Ad(&y_n, &y_n1, &y_n2, &y_n3, h, i);
		fout << i << '\t';
		for (int j = 0; j < dim; j++)
			fout << y_n[j] << '\t';
		fout << std::endl;
		if (k == step)
			return (y_n);
	}
	fout.close();
	std::cout << "Adams has done." << std::endl;
	return (y_n);
}