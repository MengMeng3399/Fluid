#include"BoundaryParticleData2.h"

BoundaryParticleData2::BoundaryParticleData2()
{

}

BoundaryParticleData2::~BoundaryParticleData2()
{

}

Vector2ArrayPtr& BoundaryParticleData2::BoundaryPosition()
{
	return _boundaryPostion;
}

DoubleArrayPtr& BoundaryParticleData2::BoundaryVolunm()
{
	return _boundaryVolunm;
}

int& BoundaryParticleData2::numberOfBoundaryParticles()
{
	return _numberOfBoundaryParticles;
}


