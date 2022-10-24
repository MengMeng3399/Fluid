#ifndef PARTICLESYSTEMSOLVER2_H
#define PARTICLESYSTEMSOLVER2_H

#include "PhysicsAnimation.h"
#include "ParticleSystemData2.h"
#include "ConstVar.h"
#include "Collision.h"
#include "NeighborSearcher2.h"
#include <iostream>
using namespace std;

class ParticleSystemSolver2 : public PhysicsAnimation {
public:
	ParticleSystemSolver2();
	~ParticleSystemSolver2();

	void setData(int numberOfParticles, int numberOfAllarticles,Vector2ArrayPtr pos, int resolutionX, int resolutionY);
	virtual void onAdvanceTimeStep(double timeIntervalInSeconds, Vector2 boundaryTop, Vector2 boundaryDown)override;
	virtual void accumulateForces(double timeIntervalInSeconds)override;


	ParticleSystemData2Ptr _particleSystemData;
	//NeighborSearcher2Ptr neighber;

protected:
	//这里用对象好呢还是用对象指针好？当然是指针了
	//shared_ptr<ParticleSystemData2> _particleSystemData;
	Collision _collider;

	void beginAdvanceTimeStep();
	void endAdvanceTimeStep();
	void timeIntegration(double timeIntervalInSeconds);
	void resolveCollision(double timeIntervalInSeconds,Vector2 boundaryTop, Vector2 boundaryDown);
	void accumlateExternalForces();
	void clearForces(Vector2ArrayPtr forces);

	//vector<bool>&  collisionState();
	Vector2ArrayPtr _newPositions;
	Vector2ArrayPtr _newVelocities;
	//vector<bool>_collisionState;
};

#endif
