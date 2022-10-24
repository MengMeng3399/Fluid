#ifndef SPHSYSTEMDATA2_H
#define SPHSYSTEMDATA2_H

#include "ParticleSystemData2.h"
#include"ParticleSystemSolver2.h"
#include <vector>
#include"SphStdKernel2.h"
//#include"poly_6.h"
using namespace std;

#include "vector2.h"
#include "DoubleArray.h"



class SphSystemData2 : public ParticleSystemData2 {
public:
	SphSystemData2();
	~SphSystemData2();
    //√‹∂»
	DoubleArrayPtr& densities();
	//—π¡¶œÓ
	DoubleArrayPtr& pressure();

	double sumOfKernelNearby(size_t i, DoubleArrayPtr boundary_volunm);
	void updateDensities(DoubleArrayPtr boundary_volunm);
	Vector2 gradientAt(size_t i,const DoubleArrayPtr values);
	double laplacianAt(size_t i, const DoubleArrayPtr values);
//	int numberOfFluidParticles();

	//------------------------?????????????------------------
//	double targetDensity();

private:
	DoubleArrayPtr _densities;
	DoubleArrayPtr _pressure;
//	int _numberOfFluidParticles;
//	double _targetDensity;
};

using SphSystemData2Ptr = shared_ptr<SphSystemData2>;

#endif
