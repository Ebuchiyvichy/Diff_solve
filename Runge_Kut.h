#pragma once

#include "function.h"

void run_k_2_2(std::vector<double> u0, double T, double h)
{
	std::vector<double> k_n1(dim);
	std::vector<double> k_n2(dim);
	std::ofstream fout;

	fout.open("Runge_Kut_2_2.txt");
	for (double i = 0; i <= T; i += h)
	{
		fout << i << '\t' << u0[0] << '\t' << u0[1] << std::endl;
		k_n1 = func(u0);
		k_n2 = func(u0 + h * k_n1);
		u0 = u0 + h * (0.5 * k_n1 + 0.5 * k_n2);
	}
	fout.close();
	std::cout << "Runge-Kutte runk 2 order 2 has done." << std::endl;
}