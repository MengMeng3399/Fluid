#ifndef SPHSPIKYKERNEL2_H
#define SPHSPIKYKERNEL2_H

#include "ConstVar.h"
#include"Vector2.h"

struct SphSpikyKernel2
{
	double h, h2, h3,h4,h5;
	SphSpikyKernel2();
	SphSpikyKernel2(double kernelRadius);
	double operator()(double distance)const;

	//-------------------以下三个函数都是对单个粒子--------------------------
	double firstDerivative(double distance)const;
	Vector2 gradent(double distance, const Vector2 direction) const;
	double secondDerivative(double distance) const;
};

inline SphSpikyKernel2::SphSpikyKernel2()
	: h(0), h2(0), h3(0),h4(0), h5(0) {}

inline SphSpikyKernel2::SphSpikyKernel2(double kernelRadius)
	: h(kernelRadius), h2(h* h), h3(h2* h),h4(h2*h2), h5(h2* h3) {}

inline double SphSpikyKernel2 :: operator()(double distance)const
{
	if (distance >=h)
	{
		return 0.0;
	}
	else
	{
		double x = 1.0 -  distance / h;

		return 15.0 / (kPiD * h3) * x * x * x;
	}
}

inline double SphSpikyKernel2::firstDerivative(double distance) const
{
	//粒子之间的距离大于核半径，作用力为0
	if (distance >= h)
	{
		return 0.0;
	}
	else
	{

		double x = 1.0 - distance / h;
		return -45.0 / (kPiD * h4) * x * x;
	}
}

inline Vector2 SphSpikyKernel2::gradent(double distance, const Vector2 direction) const
{
	return  direction * (-firstDerivative(distance));
}

inline double SphSpikyKernel2::secondDerivative(double distance)const
{
	if (distance  >= h)
	{
		return 0.0;
	}
	else
	{
		double x = 1.0-distance/ h;
		return 90.0/(kPiD*h5);
	}
}

#endif

