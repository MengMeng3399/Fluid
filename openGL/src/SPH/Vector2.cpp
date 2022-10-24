#include"vector2.h"
#include<cmath>
Vector2::Vector2() :
	_x(0.0),
	_y(0.0) {}

Vector2::Vector2(const double& x, const double& y) :
	_x(x)
	, _y(y) {}

Vector2::~Vector2() {

}

Vector2 Vector2::operator+(const Vector2& vec) const {
	Vector2 result(this->_x + vec._x, this->_y + vec._y);
	return result;
}

Vector2 Vector2::operator-(const Vector2& vec) const {
	Vector2 result(this->_x - vec._x, this->_y - vec._y);
	return result;
}

Vector2 Vector2::operator*(const double& r) const {
	Vector2 result(this->_x * r, this->_y * r);
	return result;
}

Vector2 Vector2::operator/(const double& r) const {
	Vector2 result(this->_x / r, this->_y / r);
	return result;
}

double Vector2::dot(const Vector2& vec) const {
	return this->_x * vec._x + this->_y * vec._y;
}

double Vector2::getLength()const {
	double length = sqrt(this->_x * this->_x + this->_y * this->_y);
	return length;
}

Vector2 Vector2::normalize() {
	double length = getLength();
	this->_x /= length;
	this->_y /= length;
	return *this;
}

double Vector2::cross(const Vector2& vec)const {
	return (_x * vec._y - vec._x * _y);
}

double Vector2::dis(const Vector2& vec)const {
	auto result = sqrt((vec._x - _x) * (vec._x - _x) + (vec._y - _y) * (vec._y - _y));
	return result;
}

Vector2 Vector2::operator=(const Vector2& vec) {
	this->_x = vec._x;
	this->_y = vec._y;
	return *this;
}
 //vec指向this的方向
Vector2 Vector2::direct(const Vector2& vec)const    
{
	Vector2 temp= vec- (*this);
	return  temp.normalize();
}


double& Vector2::x() {
	return _x;
}

double& Vector2::y() {
	return _y;
}
