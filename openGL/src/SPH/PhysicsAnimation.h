#ifndef PHYSICSANIMATION_H
#define PHYSICSANIMATION_H
#include"Vector2.h"

class PhysicsAnimation {
public:
	PhysicsAnimation();
	~PhysicsAnimation();
	virtual void onAdvanceTimeStep(double timeIntervalInSeconds, Vector2 boundaryTop, Vector2 boundaryDown) = 0;
	virtual void accumulateForces(double timeIntervalInSeconds) = 0;
};

#endif
