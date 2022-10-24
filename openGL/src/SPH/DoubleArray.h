#ifndef DOUBLEARRAY_H
#define DOUBLEARRAY_H
#include <vector>
#include <iostream>
using namespace std;

class DoubleArray {
public:
	DoubleArray();
	DoubleArray(const vector<double>& data);
	~DoubleArray();
public:
	vector<double>::iterator iterBegin();
	vector<double>::iterator iterEnd();
	double lookAt(size_t idx);
	double& operator[](size_t idx);
	void reSize(size_t n);
private:
	vector<double> _data;

};

using DoubleArrayPtr = shared_ptr<DoubleArray>;


#endif