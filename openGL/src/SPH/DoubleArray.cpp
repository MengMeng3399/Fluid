#include "DoubleArray.h"

DoubleArray::DoubleArray() {

}


DoubleArray::DoubleArray(const vector<double>& data) {
	_data = data;
}

DoubleArray::~DoubleArray() {

}

vector<double>::iterator DoubleArray::iterBegin() {
	return _data.begin();
}

vector<double>::iterator DoubleArray::iterEnd() {
	return _data.end();
}

double DoubleArray::lookAt(size_t idx) {
	return _data[idx];
}

double& DoubleArray::operator[](size_t idx) {
	return _data[idx];
}
void DoubleArray::reSize(size_t n)
{
	_data.resize(n);
}