#pragma once

#include "function.h"

std::vector<double> run_run(std::vector<double> u0, std::vector<double> tmp, double h, int p) //u0 - начальное значение; tmp - значение в yn, p - порядок
{
	std::vector<double> k_n1(dim), k_n2(dim);
	h /= 2;
	for (int i = 0; i != 2; i++)
	{
		k_n1 = func(u0);
		k_n2 = func(u0 + h * k_n1);
		if (p == 4)
		{
			std::vector<double> k_n3(func(u0 + h / 2 * k_n2));
			std::vector<double> k_n4(func(u0 + h * k_n3));
			u0 = u0 + h * (1.0 / 6.0) * (k_n1 + 2 * k_n2 + 2 * k_n3 + k_n4);
		}
		else u0 = u0 + h * (0.5 * k_n1 + 0.5 * k_n2);
	}
	if (norm((u0) / (pow(2, p) - 1), (tmp) / (pow(2, p) - 1)) <= EPS)
		return (u0);

	return(tmp);
}

double	min(double a, double b)
{
	if (a > b)
		return b;
	else
		return a;
}

double	max(double a, double b)
{
	if (a > b)
		return a;
	else
		return b;
}

std::vector<double> run_k_2_2(std::vector<double> u0, double T, double h, int flag)
{
	std::vector<double> k_n1(dim);
	std::vector<double> k_n2(dim);
	std::ofstream fout;
	double				facmax = 2;
	double				facmin = 0.2;
	double				fac = 0.89;
	int					k = 0;

	fout.open("Runge_Kut_2_2.txt");
	for (double i = 0; i <= T; i += h)
	{
		k++;
		std::vector<double> tmp(u0);
		fout << i << '\t';
		for (int j = 0; j < dim; j++)
			fout << u0[j] << '\t';
		fout << std::endl;
		k_n1 = func(u0);
		k_n2 = func(u0 + h * k_n1);
		u0 = u0 + h * (0.5 * k_n1 + 0.5 * k_n2);
		if (k == 5)
			return u0;
		if (flag == 1) {
			if (u0 == run_run(tmp, u0, h, 2)) {
				h *= min(facmax, max(facmin, fac * pow(h / EPS, 5)));
				continue;
			}
			if ((norm((u0) / (pow(2, 2) - 1), (run_run(tmp, u0, h, 2))) / (pow(2, 2) - 1)) < (EPS*0.1))
				h *= 2;
			u0 = run_run(tmp, u0, h, 2);
		}
	}
	fout.close();
	std::cout << "Runge-Kutte runk 2 order 2 has done." << std::endl;
	return u0;
}

void run_k_2_02(std::vector<double> u0, double T, double h, int flag)
{
	std::vector<double> k_n1(dim);
	std::vector<double> k_n2(dim);
	std::ofstream fout;

	fout.open("Runge_Kut_2_02.txt");
	for (double i = 0; i <= T; i += h)
	{
		fout << i << '\t';
		for (int j = 0; j < dim; j++)
			fout << u0[j] << '\t';
		fout << std::endl;
		k_n1 = func(u0);
		k_n2 = func(u0 + h / 2 * k_n1);
		u0 = u0 + h * k_n2;
	}
	fout.close();
	std::cout << "Runge-Kutte runk 2 order 2 another ones has done." << std::endl;
}

std::vector<double> run_k_4_4(std::vector<double> u0, double T, double h, int flag, char nbr)
{
	std::vector<double> k_n1(dim);
	std::vector<double> k_n2(dim);
	std::vector<double> k_n3(dim);
	std::vector<double> k_n4(dim);
	std::ofstream fout;
	std::string str = "Runge_Kut_4_4_";
	double				facmax = 2;
	double				facmin = 0.2;
	double				fac = 0.89;
	int					k = 0;

	str += std::to_string(nbr);
	str += ".txt";
	std::cout << str << std::endl;
	fout.open(str);
	for (double i = 0; i <= T; i += h)
	{
		k++;
		std::vector<double> tmp(u0);
		fout << i << '\t';
		for (int j = 0; j < dim; j++)
			fout << u0[j] << '\t';
		fout << std::endl;
		k_n1 = func(u0);
		k_n2 = func(u0 + h / 2 * k_n1);
		k_n3 = func(u0 + h / 2 * k_n2);
		k_n4 = func(u0 + h * k_n3);
		u0 = u0 + h * (1.0 / 6.0) * (k_n1 + 2 * k_n2 + 2 * k_n3 + k_n4);
		if (k == 5)
			return u0;
		if (flag == 1) {
			if (tmp == run_run(tmp, u0, h, 4)) {
				h *= min(facmax, max(facmin, fac * pow(h / EPS, 5)));
				continue;
			}
			u0 = run_run(tmp, u0, h, 2);
			if ((norm((u0) / (pow(2, 4) - 1), (run_run(tmp, u0, h, 4))) / (pow(2, 4) - 1)) < (EPS*0.1))
				h *= 2;
		}
	}
	fout.close();
	std::cout << "Runge-Kutte runk 4 order 4 another ones has done." << std::endl;
	return u0;
}