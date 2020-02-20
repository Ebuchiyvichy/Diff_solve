//
// Created by irina on 12.02.2020.
//
#include "equation.h"

int main(void)
{
	setlocale(LC_ALL, "Russian");
    std::cout << "Введите номер теста: ";
    int TEST; std::cin >>  TEST;
    double T; double h = 0.003;
    std::vector<double> u0(dim);
	std::vector<double> y(dim);
    test_init(TEST, &u0, &T);// инициализация начальных краевых условий и временного интервала
    int n = (T-t0)/h; // количество разбиений сетки
	eiler_explicit(u0, T, h);
//	eiler_implicit(u0, T, h);//работает в лучшем случае при 0,003 шаге
//	sym_scheme(u0, T, h);
	run_k_2_2(u0, T, h);

	system("pause");

    return 0;
}