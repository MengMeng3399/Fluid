#ifndef SPHSYSTEMSOLVER2_H
#define SPHSYSTEMSOLVER2_H

#include "ParticleSystemSolver2.h"
#include"SphSystemData2.h"
#include"DoubleArray.h"
#include"Vector2Array.h"
#include"SphStdKernel2.h"
#include"SphSpikyKernel2.h"
#include"Versatile Rigid-fluid Coupling.h"

class SphSystemSolver2 : public ParticleSystemSolver2 {
public:
	SphSystemSolver2();
	~SphSystemSolver2();
	void setData(int numberOfParticles,int numberOfAllarticles, Vector2ArrayPtr pos,
		         int resolutionX, int resolutionY);
	virtual void onAdvanceTimeStep(double timeStepInSeconds,Vector2 boundaryTop, Vector2 boundaryDown)override;
	//书里用的是强制类型转换，把基类强制转换为派生类
	//还没搞明白dynamic_pointer_cast的用法，暂且不用
	SphSystemData2Ptr& sphSystemData();
	BoundaryPtr& BoundarySystem();
protected:

	void accumulateForces(double timeStepInSeconds)override;

	void beginAdvanceTimeStep();
	//计算非压力项，包括重力，空气阻力，粘性力，（伪粘性力？）
	virtual void accumulateNonPressureForce(double timeStepInSeconds);
	//计算压力项，包括表面张力，压力
	virtual void accumulatePressureForce(double timeStepInSeconds);
	//等效于求表面张力,求出pressure[],为标量？？-----------------------------------------------;
	void computePressure();
	//状态方程，计算prssure
	double computerPressureFromEos(double density, double targetDensity, double eosScale, 
		                            double eosExponent,double negativePressureScale);
	//粘性力项
	void accumulateViscosityForce();
	//伪粘性力项,未实现
	void computePseudoViscosity();
	//重载accumulatePressureForce（）求压力项
	void accumulatePressureForce(Vector2ArrayPtr pos, DoubleArrayPtr densities, DoubleArrayPtr pressure, Vector2ArrayPtr forces);
	//将更新完成的边界坐标加入系统中
	void To_Updata_Move_Boundary();
private:
	SphSystemData2Ptr _sphSystemData;


	//以防边界处理出错，以下为边界处理需要的内容。
	//基本设想：搜索邻居时需要搜索边界，所以将流体粒子与边界粒子存储在一起，先放流体后放边界。

	BoundaryPtr _boundary;
};

#endif