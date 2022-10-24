#ifndef PARTICLESYSTEMDATA2_H
#define PARTICLESYSTEMDATA2_H

#include <vector>
#include "vector2.h"
#include "Vector2Array.h"
#include "NeighborSearcher2.h"
#include "DoubleArray.h"
using namespace std;


//-------------------粒子的相关数据-----------------


class ParticleSystemData2 {
public:
	ParticleSystemData2();

	~ParticleSystemData2();
	int& numberOfParticles();
	int& numberOfAllParticles();

	Vector2ArrayPtr &positions();
	Vector2ArrayPtr &velocities();
	Vector2ArrayPtr &forces();
	NeighborSearcher2Ptr neighbor;

private:
	Vector2ArrayPtr _positions;
	Vector2ArrayPtr _velocities;
	Vector2ArrayPtr _forces;
	int _numberOfParticles = 0;
	int _numberOfAllParticles = 0;
};

using ParticleSystemData2Ptr = shared_ptr<ParticleSystemData2>;

#endif