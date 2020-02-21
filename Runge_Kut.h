#pragma once

#include "function.h"

std::vector<double> run_run(std::vector<double> u0, std::vector<double> tmp,  double h, int p) //u0 - начальное значение; tmp - значение в yn, p - порядок
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
    if (norm((u0)/(pow(2,p)-1),(tmp)/(pow(2,p)-1)) <= EPS)
        return (u0);

    return(tmp);
}

void run_k_2_2(std::vector<double> u0, double T, double h, int flag)
{
	std::vector<double> k_n1(dim);
	std::vector<double> k_n2(dim);
	std::ofstream fout;

	fout.open("Runge_Kut_2_2.txt");
	for (double i = 0; i <= T; i += h)
	{
	    std::vector<double> tmp(u0);
		fout << i << '\t' << u0[0] << '\t' << u0[1] << std::endl;
		k_n1 = func(u0);
		k_n2 = func(u0 + h * k_n1);
		u0 = u0 + h * (0.5 * k_n1 + 0.5 * k_n2);
		if (flag == 1) {
		    if ( u0 == run_run(tmp, u0, h, 2)) {
                h /= 2;
                continue;
            }
            if ((norm((u0)/(pow(2,2)-1),(run_run(tmp, u0, h, 2)))/(pow(2,2)-1)) < (EPS*0.1))
                h *= 2;
            u0 = run_run(tmp, u0, h, 2);
        }
	}
	fout.close();
	std::cout << "Runge-Kutte runk 2 order 2 has done." << std::endl;
}

void run_k_2_02(std::vector<double> u0, double T, double h, int flag)
{
	std::vector<double> k_n1(dim);
	std::vector<double> k_n2(dim);
	std::ofstream fout;

	fout.open("Runge_Kut_2_02.txt");
	for (double i = 0; i <= T; i += h)
	{
		fout << i << '\t' << u0[0] << '\t' << u0[1] << std::endl;
		k_n1 = func(u0);
		k_n2 = func(u0 + h / 2 * k_n1);
		u0 = u0 + h * k_n2;
	}
	fout.close();
	std::cout << "Runge-Kutte runk 2 order 2 another ones has done." << std::endl;
}

void run_k_4_4(std::vector<double> u0, double T, double h, int flag)
{
	std::vector<double> k_n1(dim);
	std::vector<double> k_n2(dim);
	std::vector<double> k_n3(dim);
	std::vector<double> k_n4(dim);
	std::ofstream fout;

	fout.open("Runge_Kut_4_4.txt");
	for (double i = 0; i <= T; i += h)
	{
	    std::vector<double> tmp(u0);
		fout << i << '\t' << u0[0] << '\t' << u0[1] << std::endl;
		k_n1 = func(u0);
		k_n2 = func(u0 + h / 2 * k_n1);
		k_n3 = func(u0 + h / 2 * k_n2);
		k_n4 = func(u0 + h * k_n3);
		u0 = u0 + h * (1.0 / 6.0) * (k_n1 + 2 * k_n2 + 2 * k_n3 + k_n4);
        if (flag == 1) {
            if ( tmp == run_run(tmp, u0, h, 4)) {
                h /= 2;
                continue;
            }
            u0 = run_run(tmp, u0, h, 2);
            if ((norm((u0)/(pow(2,4)-1),(run_run(tmp, u0, h, 4)))/(pow(2,4)-1)) < (EPS*0.1))
                h *= 2;
        }
	}
	fout.close();
	std::cout << "Runge-Kutte runk 4 order 4 another ones has done." << std::endl;
}
