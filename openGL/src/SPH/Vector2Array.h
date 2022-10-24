#ifndef VECTOR2ARRAY_H
#define VECTOR2ARRAY_H

#include "vector2.h"
#include <vector>
#include <iostream>
using namespace std;

class Vector2Array {
public:
	Vector2Array();
	Vector2Array(const vector<Vector2>& data);
	~Vector2Array();
public:

	vector<Vector2>::iterator iterBegin();
	vector<Vector2>::iterator iterEnd();
	Vector2 lookAt(size_t idx);
	Vector2& operator[](size_t idx);
	void reSize(size_t n);
	size_t length();
private:
	vector<Vector2> _data;
};

using Vector2ArrayPtr = shared_ptr<Vector2Array>;

#endif