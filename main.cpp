//
// Created by irina on 12.02.2020.
//
#include "equation.h"

int main()
{
    std::cout << "Введите номер теста: ";
    std::cin >> int TEST;
    double t0 = 0;
    int dim = 2;
    std::vector<double> u0(dim); std::vector<double> y(dim);
    // инициализация начальных краевых условий и временного интервала
    test_init(TEST, u0, &T);
    int n = (T-t0)/h; // количество разбиений сетки


    return 0;
}