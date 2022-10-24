#include "SphSystemData2.h"

SphSystemData2::SphSystemData2() {
}

SphSystemData2::~SphSystemData2() {

}

DoubleArrayPtr& SphSystemData2::densities()
{
	return _densities;
}

DoubleArrayPtr& SphSystemData2::pressure()
{
	return _pressure;
}
//double SphSystemData2::targetDensity()
//{
//	return _targetDensity;
//}

void SphSystemData2::updateDensities(DoubleArrayPtr boundary_volunm)
{

	auto p = positions();
	auto d =densities();
	auto index =numberOfParticles();


	for (int i = 0; i < index; i++)
	{
		double sum = sumOfKernelNearby(i, boundary_volunm);
		//cout << sum << "--------------" << endl;

		//在DoubleArray中重写了[],返回应用所以存入d[]中相当于存入_densities[]中。
		if (sum == 0.0)
		{
			(*d)[i] =0.1;
		}
		else
		{
			(*d)[i] =sum;
		}
	   //	cout << (*d)[i] << "---------" << endl;
	}
	  //  cout << "结束一次" << endl;
}

double SphSystemData2::sumOfKernelNearby(size_t origin, DoubleArrayPtr boundary_volunm)
{
	auto p = positions();
	//auto d = densities();
	double sum = 0.0;
	SphStdKernel2 kernel(kernelRadius);
	//Poly_6 kernel(kernelRadius);
	//temp1中存放所有粒子的邻居
	auto temp1 = neighbor->neighBors();
	auto number = numberOfParticles();
	auto boundaryVolunm = boundary_volunm;
	//temp2中存放目标粒子的邻居
	auto temp2 = temp1[origin];
	size_t boundaryIndex;
	for (auto iter = temp2.begin(); iter != temp2.end(); iter++)
	{
		//目标粒子到邻居的距离
		double dist = (p->lookAt(origin)).dis(p->lookAt(*iter));
		if (dist >0)
		{
			if ((*iter) < number)
			{
				//	cout << dist << "-------------" << endl;
				sum += _mass * kernel(dist);
				//cout << sum << "--------------" << endl;
			}
			else
			{
				boundaryIndex = (*iter) - number;
				sum += boundary_density * kernel(dist) * (*boundaryVolunm)[boundaryIndex];
			}
		}
	}

	//cout << "这是sum" << endl;
	//cout << sum << "--------------" << endl;
	return sum;

}


Vector2 SphSystemData2::gradientAt(size_t i, const DoubleArrayPtr values)
{
	Vector2 sum;
	auto p = positions();
	auto d = densities();
	SphStdKernel2 kernel(kernelRadius);
	//temp1中存放所有粒子的邻居
	auto temp1 = neighbor->neighBors();
	//temp2中存放目标粒子的邻居
	auto temp2 = temp1[i];
	for (auto iter = temp2.begin(); iter != temp2.end(); iter++)
	{
		//目标粒子到邻居的距离
		//double dist = ((*p)[i]).dis((*p)[*iter]);
		double dist = (p->lookAt(i)).dis(p->lookAt(*iter));
		if (dist > 0.0)
		{   //目标粒子到邻居的方向
			Vector2 dir = ((*p)[i]).direct((*p)[*iter]);

			sum = sum + kernel.gradent(dist, dir) *
				(*d)[i] * _mass *
				((*values)[i] / ((*d)[i] * (*d)[i]) + (*values)[*iter] / ((*d)[*iter] * (*d)[*iter]));

		}
	}
	return sum;

}

double SphSystemData2::laplacianAt(size_t i, const DoubleArrayPtr values)
{
	double sum=0.0;
	auto p = positions();
	auto d = densities();

	SphStdKernel2 kernel(kernelRadius);
	//temp1中存放所有粒子的邻居
	auto temp1 = neighbor->neighBors();
	//temp2中存放目标粒子的邻居序号
	auto temp2 = temp1[i];
	for (auto iter = temp2.begin(); iter != temp2.end(); iter++)
	{
		//目标粒子到邻居的距离
		//double dist = ((*p)[i]).dis((*p)[*iter]);
		double dist = (p->lookAt(i)).dis(p->lookAt(*iter));
		sum += _mass * (*values)[*iter]/ (*d)[*iter] * kernel.secondDerivative(dist);
	}
	return sum;

}


//int SphSystemData2::numberOfFluidParticles()
//{
//	return _numberOfFluidParticles;
//}