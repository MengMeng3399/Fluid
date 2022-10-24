#pragma once
#include <vector>
#include "vector2.h"
#include "Vector2Array.h"
#include "NeighborSearcher2.h"
#include "DoubleArray.h"
using namespace std;

class BoundaryParticleData2
{
public:
	BoundaryParticleData2();

	~BoundaryParticleData2();

	Vector2ArrayPtr& BoundaryPosition();

	DoubleArrayPtr& BoundaryVolunm();

	int& numberOfBoundaryParticles();

	NeighborSearcher2Ptr neighbor;

private:

	Vector2ArrayPtr _boundaryPostion;

	DoubleArrayPtr _boundaryVolunm;

	int  _numberOfBoundaryParticles;

//	NeighborSearcher2Ptr _neighbor;

};
using BoundaryParticleData2Ptr = shared_ptr<BoundaryParticleData2>;
