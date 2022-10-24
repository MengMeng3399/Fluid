#include "ParticleSystemData2.h"

ParticleSystemData2::ParticleSystemData2() {
}

ParticleSystemData2::~ParticleSystemData2() {

}

int& ParticleSystemData2::numberOfParticles() {
	return _numberOfParticles;
}

Vector2ArrayPtr& ParticleSystemData2::positions() {
	return _positions;
}

Vector2ArrayPtr& ParticleSystemData2::velocities() {
	return _velocities;
}

Vector2ArrayPtr& ParticleSystemData2::forces() {
	return _forces;
}

int& ParticleSystemData2::numberOfAllParticles()
{
	return _numberOfAllParticles;
}
