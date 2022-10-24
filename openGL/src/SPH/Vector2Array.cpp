#include "Vector2Array.h"

Vector2Array::Vector2Array() {

}

Vector2Array::Vector2Array(const vector<Vector2>& data) {
	_data = data;
}

Vector2Array::~Vector2Array() {

}

vector<Vector2>::iterator Vector2Array::iterBegin() {
	return _data.begin();
}

vector<Vector2>::iterator Vector2Array::iterEnd() {
	return _data.end();
}

Vector2 Vector2Array::lookAt(size_t idx) {
	return _data[idx];
}

Vector2& Vector2Array::operator[](size_t idx) {
	return _data[idx];
}

void Vector2Array::reSize(size_t n) {
	_data.resize(n);
}

size_t Vector2Array::length() {
	return _data.size();
}