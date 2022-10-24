#ifndef SPHSTDKERNEL2_H
#define SPHSTDKERNEL2_H

#include "ConstVar.h"
#include"Vector2.h"

struct SphStdKernel2 
{
	double h, h2, h3,h5;
	SphStdKernel2();
	SphStdKernel2(double kernelRadius);
	double operator()(double distance)const;

	//-------------------以下三个函数都是对单个粒子--------------------------
	double firstDerivative(double distance)const;
	Vector2 gradent(double distance, const Vector2 direction) const;
	double secondDerivative(double distance) const;
};

inline SphStdKernel2::SphStdKernel2()
	: h(0), h2(0), h3(0),h5(0) {}

inline SphStdKernel2::SphStdKernel2(double kernelRadius)
	: h(kernelRadius), h2(h* h), h3(h2* h),h5(h2*h3) {}

inline double SphStdKernel2 :: operator()(double distance)const 
{
	if (distance * distance >= h2) 
	{
		return 0.0;
	}
	else 
	{
		double x = 1.0 - distance * distance / h2;
		//cout << "X=" <<x<< "------------" << endl;
		auto result= 315.0 / (64.0 * kPiD * h3) * x * x * x;
		//cout <<"result="<< result << "------------" << endl;
		return result;
	}
}

inline double SphStdKernel2::firstDerivative(double distance) const
{
	//粒子之间的距离大于核半径，作用力为0
	if (distance >= h)
	{
		return 0.0;
	}
	else
	{
	
		double x = 1.0 - distance * distance / h2;
		return -945.0 / (32.0 * kPiD * h5) * distance * x * x;
	}
}

inline Vector2 SphStdKernel2::gradent(double distance, const Vector2 direction) const
{
	return  direction * (-firstDerivative(distance));
}

inline double SphStdKernel2::secondDerivative(double distance)const
{
	if (distance * distance >= h2)
	{
		return 0.0;
	}
	else
	{
		double x = distance * distance / h2;
		return 945.0 / (32.0 * kPiD * h5) * (1 - x) * (5 * x - 1);
	}
}

#endif
