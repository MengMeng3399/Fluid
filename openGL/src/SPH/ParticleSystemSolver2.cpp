#include "ParticleSystemSolver2.h"

ParticleSystemSolver2::ParticleSystemSolver2() {
	_particleSystemData = make_shared<ParticleSystemData2>();
	_newPositions = make_shared<Vector2Array>();
	_newVelocities = make_shared<Vector2Array>();


}

ParticleSystemSolver2::~ParticleSystemSolver2() {

}

//初始化，之后时间积分只需要更新。
void ParticleSystemSolver2::setData(int numberOfParticles, int numberOfAllarticles,Vector2ArrayPtr pos, int resolutionX, int resolutionY)
{
	_particleSystemData->numberOfParticles() = numberOfParticles;
	_particleSystemData->positions() = pos;
	_particleSystemData->numberOfAllParticles() = numberOfAllarticles;

	//for (int i = 0; i < numberOfParticles; i++)
	//{
	//	auto temp = _particleSystemData->positions();

	//	cout <<(*temp)[i].x() << endl;
	//}
	
	vector<Vector2> tempV;

	for (int i = 0; i < numberOfAllarticles; ++i)
	{
		Vector2 v;
		tempV.push_back(v);
		
	}
	_particleSystemData->velocities() = make_shared<Vector2Array>(tempV);
	_particleSystemData->forces() = make_shared<Vector2Array>(tempV);
	
	//_particleSystemData->velocities() = make_shared<Vector2Array>();
	//_particleSystemData->velocities()->reSize(numberOfParticles);
	//_particleSystemData->velocities() = vel;
	//_particleSystemData->forces() = forces;
	//_particleSystemData->forces() = make_shared<Vector2Array>();
	//_particleSystemData->forces()->reSize(numberOfParticles);
	

	_particleSystemData->neighbor = make_shared<NeighborSearcher2>(resolutionX, resolutionY, numberOfAllarticles);
}

void ParticleSystemSolver2::beginAdvanceTimeStep() {
	size_t n = _particleSystemData->numberOfParticles();
	//size_t n = _particleSystemData->numberOfAllParticles();
	_newPositions->reSize(n);
	_newVelocities->reSize(n);
	_particleSystemData->neighbor->setNeiborList(_particleSystemData->positions());
	clearForces(_particleSystemData->forces());
}

void ParticleSystemSolver2::endAdvanceTimeStep() {
	size_t n = _particleSystemData->numberOfParticles();
	auto positions = _particleSystemData->positions();
	auto velocities = _particleSystemData->velocities();
	//auto state = collisionState();

	for (size_t i = 0; i < n; ++i) {
		(*velocities)[i] = (*_newVelocities)[i];
		(*positions)[i] = (*_newPositions)[i];
	}
}

void ParticleSystemSolver2::timeIntegration(double timeIntervalInSeconds) {
	size_t n = _particleSystemData->numberOfParticles();
	auto forces = _particleSystemData->forces();
	auto velocities = _particleSystemData->velocities();
	auto positions = _particleSystemData->positions();
	double mass = 1.0;

	for (size_t i = 0; i < n; ++i) {
		auto& newVelocity = (*_newVelocities)[i];
		auto temp1 = (*velocities)[i] + ((*forces)[i] / mass) * timeIntervalInSeconds;
		newVelocity = temp1;

		auto& newPosition = (*_newPositions)[i];
		auto temp2 = (*positions)[i] + newVelocity * timeIntervalInSeconds;
		newPosition = temp2;
	}

}

void ParticleSystemSolver2::resolveCollision(double timeIntervalInSeconds, Vector2 boundaryTop, Vector2 boundaryDown) 
{
	size_t n = _particleSystemData->numberOfParticles();
//	vector<bool> state;
	for (size_t i = 0; i < n; ++i) {
		auto& newPosition = (*_newPositions)[i];
		auto& newVelocity = (*_newVelocities)[i];
		_collider.resolveCollision(newPosition, newVelocity, timeIntervalInSeconds,boundaryTop,boundaryDown);

	}
}

void ParticleSystemSolver2::onAdvanceTimeStep(double timeIntervalInSeconds,Vector2 boundaryTop, Vector2 boundaryDown) 
{
	beginAdvanceTimeStep();
	accumulateForces(timeIntervalInSeconds);
	timeIntegration(timeIntervalInSeconds);
	resolveCollision(timeIntervalInSeconds, boundaryTop, boundaryDown);
	endAdvanceTimeStep();
}


void ParticleSystemSolver2::accumulateForces(double timeIntervalInSeconds) {
	accumlateExternalForces();
}

void ParticleSystemSolver2::accumlateExternalForces() {
	//Gravity
	size_t n = _particleSystemData->numberOfParticles();
	auto forces = _particleSystemData->forces();
	auto velocities = _particleSystemData->velocities();
	auto positions = _particleSystemData->positions();
	//double mass = 1.0;

	//重力

	for (size_t i = 0; i < n; ++i) {
		auto force = GRAVITY * _mass;
		(*forces)[i] = (*forces)[i] + force;
	}

	//阻力
	//简单的在速度方向有一个衰减。

	for (size_t i = 0; i < n; ++i)
	{
		auto force = (*velocities)[i] * dragCoefficient;
		(*forces)[i] = (*forces)[i] - force;
	}
}

void ParticleSystemSolver2::clearForces(Vector2ArrayPtr forces) {
	Vector2 zero;
	for (auto iter = forces->iterBegin(); iter != forces->iterEnd(); iter++) {
		*iter = zero;
	}

}

