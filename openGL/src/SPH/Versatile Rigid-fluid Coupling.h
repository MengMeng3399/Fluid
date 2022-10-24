#pragma once
#include "Vector2.h"
#include"Vector2Array.h"
#include"DoubleArray.h"
#include"BoundaryParticleData2.h"
#include"SphSpikyKernel2.h"
#include<math.h>
struct Boundary
{
	//先写一个固定边界
	//手动设置边界的采样点
	//暂时理解的是计算边界粒子的体积时只需要边界粒子邻居。（不考虑流体）  

	Boundary();
	~Boundary();
	//设置边界的位置
	void  setData(int numberOfBoundaryParticles,Vector2ArrayPtr boundaryPositionint,int resolutionX, int resolutionY);
	//计算边界粒子的体积,需要当前粒子的邻居
	void boundPointVolunm();

	BoundaryParticleData2Ptr& BoundaryParticle();

private:
	BoundaryParticleData2Ptr boundaryParticle;
	int ifover = -1;
	//以下是移动边界，移动边界需要更新位置。
public:
	void Upadate_Move_Boundary(int numberOfMoveBoundary);

};

using BoundaryPtr = shared_ptr<Boundary>;