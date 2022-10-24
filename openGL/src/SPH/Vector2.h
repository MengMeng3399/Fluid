#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
public:
	Vector2();
	Vector2(const double& x, const double& y);
	~Vector2();
	Vector2 operator+(const Vector2& vec) const;
	Vector2 operator-(const Vector2& vec) const;
	Vector2 operator*(const double& r) const;
	Vector2 operator/(const double& r) const;
	Vector2 direct(const Vector2& vec)const;
	double dot(const Vector2& vec) const;
	double getLength()const;
	Vector2 normalize();
	double cross(const Vector2& vec)const;
	double dis(const Vector2& vec)const;
	Vector2 operator=(const Vector2& vec);

	double& x();
	double& y();

private:
	double _x;
	double _y;
};

#endif
