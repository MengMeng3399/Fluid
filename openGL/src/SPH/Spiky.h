#ifndef SPHSPIKYKERNEL2_H
#define SPHSPIKYKERNEL2_H

#include "ConstVar.h"
#include"Vector2.h"

struct Spiky
{
	double h, h2, h3, h4, h5,h6;
	Spiky();
	Spiky(double kernelRadius);
	double operator()(double distance)const;

	//-------------------以下三个函数都是对单个粒子--------------------------
	double firstDerivative(double distance)const;
	Vector2 gradent(double distance, const Vector2 direction) const;
//	double secondDerivative(double distance) const;
};

inline Spiky::Spiky()
	: h(0), h2(0), h3(0), h4(0), h5(0) ,h6(0){}

inline Spiky::Spiky(double kernelRadius)
	: h(kernelRadius), h2(h* h), h3(h2* h), h4(h2* h2), h5(h2* h3),h6(h3*h3) {}

inline double Spiky :: operator()(double distance)const
{
	if (distance >= h)
	{
		return 0.0;
	}
	else
	{
		double x = h-distance;

		return 15.0 / (kPiD * h6) * x * x * x;
	}
}

inline double Spiky::firstDerivative(double distance) const
{
	//粒子之间的距离大于核半径，作用力为0
	if (distance >= h)
	{
		return 0.0;
	}
	else
	{

		double x =( h - distance) / h3;
		return -45.0 / kPiD  * x * x;
	}
}

inline Vector2 Spiky::gradent(double distance, const Vector2 direction) const
{
	return  direction * (-firstDerivative(distance));
}

//inline double Spiky::secondDerivative(double distance)const
//{
//	if (distance >= h)
//	{
//		return 0.0;
//	}
//	else
//	{
//		double x = 1.0 - distance / h;
//		return 90.0 / (kPiD * h5);
//	}
//}

#endif


