//
// Created by irina on 12.02.2020.
//
#include "error.h"

int main(void)
{
	std::cout << "Please, enter the number of test: ";
	int TEST; std::cin >> TEST;
	double T; double h = 0.03;
	std::vector<double> u0(dim);
	std::vector<double> y(dim);
	double				R = 0.3;
	int					nbr = 15;

	test_init(TEST, &u0, &T);// инициализация начальных краевых условий и временного интервала
	int n = (T - t0) / h; // количество разбиений сетки
	//	eiler_explicit(u0, T, h);
	//	eiler_implicit(u0, T, h, 10000);//работает в лучшем случае при 0,003 шаге
	//	sym_scheme(u0, T, h);
	//	run_k_2_2(u0, T, h, 10000);
	//	run_k_4_4_change(u0, T, h);

	//	run_k_2_02(u0, T, h, 0);
	//	run_k_4_4(u0, T, h, 0, 0);
	/*
	for (int i = 0; i < nbr; i++)
	{
		u0[0] = 0.4 + R * cos(2 * PI * i / nbr);
		u0[1] = 3.75 - R * sin(2 * PI * i / nbr);
		run_k_4_4(u0, T, h, i, 100000);
	}*/

	for (int i = 0; i < nbr; i++)
	{
		if (i < nbr / 2)
			u0[0] = 0;
		else
			u0[0] = 3;
		u0[1] = 8 - i * 1;
		run_k_4_4(u0, T, h, i, 1000000);
	}

	//	Adams(u0, T, h, 100000);
	//	Adams_progn_correct(u0, T, h, 100000);
	//	abs_error(check_func(5 * h), u0, h, T, 5);
	//	error_eitken(u0, h, T, 5);
	//	abs_error(check_func(T), u0, h, T, 10000);//последняя точка
	//	error_eitken(u0, h, T, 10000);
	//энергия
	//	energy(u0, T, h, 10000);


	system("pause");

	return 0;
}