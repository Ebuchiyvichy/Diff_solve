//
// Created by irina on 12.02.2020.
//
#include "error.h"

int main(void)
{
	std::cout << "Please, enter the number of test: ";
	int TEST; std::cin >> TEST;
	if (TEST == 0)
		CHECK_ERR = 1;
	double T; double h = 0.07;
	std::vector<double> u0(dim);
	std::vector<double> y(dim);
	double				R = 0.8;
	int					nbr = 15;

	test_init(TEST, &u0, &T);// инициализация начальных краевых условий и временного интервала
	int n = (T - t0) / h; // количество разбиений сетки
	std::vector<double> u(dim); // эталонное решение
		//	eiler_explicit(u0, T, h);
	//	eiler_implicit(u0, T, h);//работает в лучшем случае при 0,003 шаге
	//	sym_scheme(u0, T, h);
//	run_k_2_2(u0, T, h, 10000);
		run_k_4_4_change(u0, T, h);
		run_k_2_2_change(u0, T, h);
		//	run_k_2_02(u0, T, h, 0);
	//	run_k_4_4(u0, T, h, 0, 0);
/*
	for (int i = 0; i < nbr; i++)
	{
		u0[0] = 0.1 + R * cos(2 * PI * i / nbr);
		u0[1] = 0.1 - R * sin(2 * PI * i / nbr);
		run_k_4_4(u0, T, h, 0, i, 100000);
	}

	for (int i = 0; i < nbr; i++)
	{
		u0[0] = 0;
		u0[1] = 1 - i * 0.01;
		run_k_4_4(u0, T, h, 0, i);
	}
*/
//	Adams(u0, T, h);
//	abs_error(check_func( 5 * h), u0, h, T);
//	error_eitken(check_func(5 * h), u0, h, T);

	system("pause");

	return 0;
}