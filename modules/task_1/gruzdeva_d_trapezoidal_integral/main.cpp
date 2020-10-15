// Copyright 2020 Gruzdeva Diana
#include <iostream>
#include "./trapezoidal_integral.h"

int main() {
	std::function<double(double)> first = func1;
	std::function<double(double)> second = func2;
	std::function<double(double)> third = func3;
	std::function<double(double)> fourth = func4;
	std::function<double(double)> fifth = func5;
	double c1 = trap_integral(0.0, 10.0, 1000, first);
	double c2 = trap_integral(0.0, 10.0, 1000, second);
	double c3 = trap_integral(0.0, 10.0, 1000, third);
	double c4 = trap_integral(0.0, 10.0, 1000, fourth);
	double c5 = trap_integral(0.0, 10.0, 1000, fifth);
	std::cout << c1 << std::endl;
	std::cout << c2 << std::endl;
	std::cout << c3 << std::endl;
	std::cout << c4 << std::endl;
	std::cout << c5 << std::endl;
	return 0;
}