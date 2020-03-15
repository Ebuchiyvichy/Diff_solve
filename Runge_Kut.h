#pragma once

#include "function.h"

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

std::vector<double> run_k_2_2(std::vector<double> u0, double T, double h, int step)
{
	std::vector<double> k_n1(dim);
	std::vector<double> k_n2(dim);
	std::ofstream fout;
	double				facmax = 2.0;
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
		k_n1 = func(u0);
		k_n2 = func(u0 + h * k_n1);
		u0 = u0 + h * (0.5 * k_n1 + 0.5 * k_n2);
		if (k == step)
			return u0;
	}
	fout.close();
	std::cout << "Runge-Kutte runk 2 order 2 has done." << std::endl;
	return u0;
}

std::vector<double> run_k_4_4(std::vector<double> u0, double T, double h, char nbr, int step)
{
	std::vector<double> k_n1(dim);
	std::vector<double> k_n2(dim);
	std::vector<double> k_n3(dim);
	std::vector<double> k_n4(dim);
	std::ofstream fout;
	std::string str = "Runge_Kut_4_4_";
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
		if (k == step)
			return u0;
	}
	fout.close();
	std::cout << "Runge-Kutte runk 4 order 4 has done." << std::endl;
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

int run_run_change(std::vector<double> u0, std::vector<double> tmp, double h, int p, double *norma) //u0 - íà÷àëüíîå çíà÷åíèå; tmp - çíà÷åíèå â yn, p - ïîðÿäîê
{
    std::vector<double> k_n1(dim), k_n2(dim);
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
    *norma = -log(norm((u0-tmp) / (pow(2, p) - 1)));
    if(norm((u0-tmp) / (pow(2, p) - 1)) <= EPS*0.1)
        return 2;
    if (norm((u0-tmp) / (pow(2, p) - 1)) <= EPS)
        return 0;		//øàã ïîäõîäèò
    return 1;		//øàã íå ïîäõîäèò


std::vector<double> run_k_2_2_change(std::vector<double> u0, double T, double h)
{
    std::vector<double> k_n1(dim);
    std::vector<double> k_n2(dim);
    std::ofstream fout;
    double				facmax = 2.0;
    double				facmin = 0.2;
    double				fac = 0.89;
    int					k = 0;

    fout.open("/home/irina/Documents/MetVich/Diff_solve/Runge_Kut_2_2_change.txt");
    for (double i = 0; i <= T; i += h)
    {
        k++;
        std::vector<double> tmp(u0);
        std::vector<double> u(dim);
        double				norma;

        u[0] = check_func(i);
        u[1] = check_func_dif(i);

        k_n1 = func(u0);
        k_n2 = func(u0 + 2 * h * k_n1);
        u0 = u0 + 2 * h * (0.5 * k_n1 + 0.5 * k_n2);
        if (run_run_change(tmp, u0, h, 2, &norma) == 1)
        {
            h *= min(facmax, max(facmin, fac * pow(EPS / norma, 1./3)));
            u0 = tmp;
            continue;
        }
        else if (run_run_change(tmp, u0, h, 2, &norma) == 2) {
            h *= 2;
            u0 = tmp;
            continue;
        }
        fout << i << '\t';
        for (int j = 0; j < dim; j++)
            fout << tmp[j] << '\t';
        fout << norm(tmp - u) << '\t';
        fout << -log(h) << '\t';
        fout << norma << std::endl;
    }
    fout.close();
    std::cout << "Runge-Kutte runk 2 order 2 with change has done." << std::endl;
    return u0;
}

std::vector<double> run_k_4_4_change(std::vector<double> u0, double T, double h)
{
	std::vector<double> k_n1(dim);
	std::vector<double> k_n2(dim);
	std::vector<double> k_n3(dim);
	std::vector<double> k_n4(dim);
	std::ofstream fout;
	double				facmax = 2.0;
	double				facmin = 0.2;
	double				fac = 0.89;
	int					k = 0;

	fout.open("Runge_Kut_4_4_change.txt");
	for (double i = 0; i <= T; i += h)
	{
		k++;
		std::vector<double> tmp(u0);
		std::vector<double> u(dim);
		double				norma;


		u[0] = check_func(i);
		u[1] = check_func_dif(i);
		k_n1 = func(u0);
		k_n2 = func(u0 + 2 * h * k_n1);
		k_n3 = func(u0 + 2 * h / 2 * k_n2);
		k_n4 = func(u0 + 2 * h * k_n3);
		u0 = u0 + 2 * h * (1.0 / 6.0) * (k_n1 + 2 * k_n2 + 2 * k_n3 + k_n4);
        if (run_run_change(tmp, u0, h, 4, &norma) == 1)
        {
            h *= min(facmax, max(facmin, fac * pow(EPS / norma, 1./5)));
            u0 = tmp;
            continue;
        }
        else if (run_run_change(tmp, u0, h, 4, &norma) == 2) {
            h *= 2;
            u0 = tmp;
            continue;
        }
        fout << i << '\t';
        for (int j = 0; j < dim; j++)
            fout << tmp[j] << '\t';
        fout << norm(tmp - u) << '\t';
        fout << -log(h) << '\t';
        fout << norma << std::endl;

	}
	fout.close();
	std::cout << "Runge-Kutte runk 4 order 4 with change has done." << std::endl;
	return u0;
}

std::vector<double> energy(std::vector<double> u0, double T, double h, int step)
{
     std::vector<double> k_n1(dim);
     std::vector<double> k_n2(dim);
     std::ofstream fout;
     int					k = 0;
     double				energy;
     fout.open("Energy.txt");
     for (double i = 0; i <= T; i += h)
     {
         k++;
         std::vector<double> tmp(u0);
         fout << i << '\t';
         energy = 0.03 * u0[1] * u0[1] / 2 + 20 * u0[0] * u0[0] / 2;
         fout << energy << '\n';
         k_n1 = func(u0);
         k_n2 = func(u0 + h * k_n1);
         u0 = u0 + h * (0.5 * k_n1 + 0.5 * k_n2);
         if (k == step)
             return u0;
     }
     out.close();
     std::cout << "Energy has done." << std::endl;
     return u0;
}