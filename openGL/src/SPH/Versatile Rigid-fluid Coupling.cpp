#include"Versatile Rigid-fluid Coupling.h"

Boundary::Boundary()
{
	boundaryParticle = make_shared<BoundaryParticleData2>();
	
}

Boundary::~Boundary()
{

}

void  Boundary::setData(int numberOfBoundaryParticles,Vector2ArrayPtr boundaryPosition,int resolutionX, int resolutionY)
{
	boundaryParticle->numberOfBoundaryParticles() = numberOfBoundaryParticles;
	boundaryParticle->BoundaryPosition() = boundaryPosition;

	//初始化体积（因为想用下标赋值）
	vector<double> temp(numberOfBoundaryParticles, 0.0);
	boundaryParticle->BoundaryVolunm() = make_shared<DoubleArray>(temp);
	//先暂时用流体粒子的邻居搜索，可能会很慢。
	boundaryParticle->neighbor=make_shared<NeighborSearcher2>(resolutionX, resolutionY, numberOfBoundaryParticles);
	boundaryParticle->neighbor->setNeiborList(boundaryParticle->BoundaryPosition());
}




void Boundary::boundPointVolunm()
{  
	//体积只更新一次，因为用的是固定边界。
	auto temp1 = boundaryParticle->neighbor->neighBors();
	auto numberOfParticles = boundaryParticle->numberOfBoundaryParticles();
	auto x = boundaryParticle->BoundaryPosition();
	auto& volunm = boundaryParticle->BoundaryVolunm();
	SphSpikyKernel2 kernel(kernelRadius);
	double sum;

	//不知道论文里按照哪个核函数更新的体积。先暂时采用SphSpikyKernel。效果不好再换。

	for (int i = 0; i < numberOfParticles; i++)
	{  
		sum = 0.0;
		auto temp2 = temp1[i];
		for (auto iter = temp2.begin(); iter != temp2.end(); iter++)
		{
			double dist = (x->lookAt(i)).dis(x->lookAt(*iter)); //距离
			sum += kernel(dist);
		}
		(*volunm)[i] = 1.0 / sum;
	}
}

BoundaryParticleData2Ptr& Boundary::BoundaryParticle()
{
	return boundaryParticle;
}

//----------------先写一个边界比较简单的变化---------------------------
void Boundary:: Upadate_Move_Boundary(int numberOfMoveBoundary)
{
	auto& position = BoundaryParticle()->BoundaryPosition();
	
	if ((*position)[0].x() < 0.50 || (*position)[0].x() > 1.50)
	{
		ifover = -ifover;
	}

	for (int i = 0; i < numberOfMoveBoundary; i++)
	{

		(*position)[i].x() = (*position)[i].x() + ifover * move_boundary;
	}

}