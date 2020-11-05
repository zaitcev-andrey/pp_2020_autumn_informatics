#include "./mat_mult_horiz_stripe_a.h"
#include <iostream>

int main() {
	int** a;
	int** b;
	int** c;
	a = getRandomMatrix(3, 3, time(0));
	b = getRandomMatrix(3, 3, time(0) + 1);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << a[i][j] << " ";
		}
        std::cout << std::endl;
	}
	std::cout << std::endl;
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << b[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	c = getSequentialMultiplication(a, b, 3, 3, 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << c[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}