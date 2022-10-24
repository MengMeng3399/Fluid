#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <random>
using namespace std;

double random_double(double a, double b) {
	//����һ�������Ϊ����
	std::random_device rd;

	std::mt19937 eng(rd());

	std::uniform_real_distribution<double> dis(a, b);
	return dis(eng);
}

#endif
