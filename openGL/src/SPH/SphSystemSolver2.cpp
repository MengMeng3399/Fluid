#include "SphSystemSolver2.h"

SphSystemSolver2::SphSystemSolver2() 
{
	_sphSystemData= make_shared<SphSystemData2>();
	
	_boundary = make_shared<Boundary>();
	
}

SphSystemSolver2::~SphSystemSolver2() {

}

void SphSystemSolver2::onAdvanceTimeStep(double timeStepInSeconds,Vector2 boundaryTop, Vector2 boundaryDown)
{
	beginAdvanceTimeStep();
	accumulateForces(timeStepInSeconds);
	//cout << "------------------力" << endl;
	//auto temp = _sphSystemData->forces();
	//for (int i = 0; i < 5; i++)
	//{
	//	auto tempx=(*temp)[i].x();
	//	auto tempy = (*temp)[i].y();
	//	cout << tempx << "***------*" << tempy << endl;
	//}
	ParticleSystemSolver2::timeIntegration(timeStepInSeconds);
	To_Updata_Move_Boundary();
	ParticleSystemSolver2::resolveCollision(timeStepInSeconds, boundaryTop, boundaryDown);
	ParticleSystemSolver2::endAdvanceTimeStep();
	
}
void SphSystemSolver2::accumulateForces(double timeStepInSeconds)
{
	accumulateNonPressureForce(timeStepInSeconds);
	accumulatePressureForce(timeStepInSeconds);
}

void SphSystemSolver2::accumulateNonPressureForce(double timeStepInSeconds)
{
	ParticleSystemSolver2::accumulateForces(timeStepInSeconds);

	//这不是重复计算了吗
	//accumlateExternalForces();
	//--------------------------暂时不添加粘力-------------------
	//accumulateViscosityForce();
}


void  SphSystemSolver2::setData(int numberOfParticles, int numberOfAllarticles,Vector2ArrayPtr pos,
	                             int resolutionX, int resolutionY)
{
	ParticleSystemSolver2::setData(numberOfParticles, numberOfAllarticles,pos,resolutionX,resolutionY);
	auto &particles = sphSystemData();
	vector<double> temp(numberOfAllarticles,0.0);
    //初始化密度，压力
	particles->densities() = make_shared<DoubleArray>(temp);
	particles->pressure() = make_shared<DoubleArray>(temp);

}

void SphSystemSolver2::accumulatePressureForce(double timeStepInSeconds)
{
	auto &particles = sphSystemData();
	auto x = particles->positions();
	auto d = particles->densities();
	auto p = particles->pressure();
	auto f = particles->forces();

	computePressure();
//
//cout << "------------------压强" << endl;
//auto temp = _sphSystemData->pressure();
//for (int i = 0; i < 5; i++)
//{
//	auto temp1 = (*temp)[i];
//cout << temp1 << "***------*" << endl;
//}
	
	accumulatePressureForce(x, d, p, f);

}

void SphSystemSolver2::accumulatePressureForce(Vector2ArrayPtr positions, DoubleArrayPtr densities, 
	                                           DoubleArrayPtr pressure, Vector2ArrayPtr forces)
{
	auto &particles = sphSystemData();
	auto& boundaryParticlesVolunm = _boundary->BoundaryParticle()->BoundaryVolunm();
	size_t numberOfParticles = particles->numberOfParticles();
	size_t numberOfAllParticles = particles->numberOfAllParticles();
	const double massSquared = _mass * _mass;
	const SphSpikyKernel2 kernel(kernelRadius);
	size_t boundaryIndex;
	//temp1中存放所有粒子的邻居
	auto temp1 = particles->neighbor->neighBors();

	for (int i = 0; i < numberOfParticles; i++)
	{
		
		auto temp2 = temp1[i];
		for (auto iter = temp2.begin(); iter != temp2.end(); iter++)
		{
			double dist = (positions->lookAt(i)).dis(positions->lookAt(*iter));   //距离
			//cout << dist << endl;
			//cout << positions->lookAt(i).x() << "   " << positions->lookAt(i).y() << "    " << positions->lookAt(*iter).x() << "    " << positions->lookAt(*iter).y() << endl;

			//cout << i << "," << *iter << endl;
			Vector2 dir = ((positions->lookAt(i)).direct(positions->lookAt(*iter)));  //方向
			if (dist > 0.0)
			{
				if ((*iter) < numberOfParticles)
				{
					(*forces)[i] = (*forces)[i] - kernel.gradent(dist, dir) * massSquared *
						((*pressure)[i] / ((*densities)[i] * (*densities)[i])
							+ (*pressure)[*iter] / ((*densities)[*iter] * (*densities)[*iter]));
					//cout << (*forces)[i].x() << ",     " << (*forces)[i].y() << endl;
				}
				else
				{
					boundaryIndex = (*iter) - numberOfParticles;
					(*forces)[i] = (*forces)[i] - kernel.gradent(dist, dir) * _mass * boundary_density * (*boundaryParticlesVolunm)[boundaryIndex] * ((*pressure)[i] / ((*densities)[i] * (*densities)[i]));
				}
			}
		}
			
	}
}
void SphSystemSolver2::computePressure()
{
	auto &particles = sphSystemData();
	size_t numberOfParticles = particles->numberOfParticles();
	auto d = particles->densities();
	auto p = particles->pressure();

	const double targetDensity =_targetDensity;
	double negativePressureScale = 0.0;
	const double eosScale = targetDensity * (_speedOfSound * _speedOfSound);

	for (int i = 0; i < numberOfParticles; i++)
	{
		(*p)[i] = computerPressureFromEos((*d)[i], targetDensity, eosScale, _eosExponent,negativePressureScale);
	}

	//cout << "--------压强-----------" << endl;
	//auto temp = _sphSystemData->pressure();
	//for (int i = 0; i < 5; i++)
	//{
	//	auto temp1 = (*temp)[i];
	//	cout << temp1 << "***------*" << endl;
	//}
}





double SphSystemSolver2::computerPressureFromEos(double density, double targetDensity, double eosScale, double eosExponent,
	                                             double negativePressureScale)
{
	double p = eosScale / eosExponent * (pow(density / targetDensity, eosExponent) - 1.0);

	if (p < 0) {
		p *= negativePressureScale;
	}
	return p;

}

void SphSystemSolver2::beginAdvanceTimeStep()
{
	auto &particles = sphSystemData();
	auto boundary_volunm = _boundary->BoundaryParticle()->BoundaryVolunm();
	ParticleSystemSolver2::beginAdvanceTimeStep();

	//size_t n = particles->numberOfParticles();
	//size_t n = particles->numberOfAllParticles();

	//先暂时留着 ，最后看看这步是否真的需要

	//particles->neighbor->setNeiborList(particles->positions());
	particles->updateDensities(boundary_volunm);

////-------------------密度-----------
//cout << "---------密度--------" << endl;
//
//auto temp = _sphSystemData->densities();
//for (int i = 0; i < 5; i++)
//{
//auto temp1 = (*temp)[i];
//cout << temp1 << "***------*" << endl;
//}
}



void SphSystemSolver2::accumulateViscosityForce()
{
	auto &particles = sphSystemData();
	auto x = particles->positions();
	auto v = particles->velocities();
	auto d = particles->densities();
	auto f = particles->forces();
	size_t numberOfParticles = particles->numberOfParticles();

	const double massSquared = _mass * _mass;
	const SphSpikyKernel2 kernel(kernelRadius);
	//temp1中存放所有粒子的邻居

	auto temp1 = particles->neighbor->neighBors();

	for (int i = 0; i < numberOfParticles; i++)
	{
		auto temp2 = temp1[i];
		for (auto iter = temp2.begin(); iter != temp2.end(); iter++)
		{
			double dist = (x->lookAt(i)).dis(x->lookAt(*iter)); //距离
			(*f)[i]= (*f)[i]+((*v)[*iter] - (*v)[i]) / (*d)[*iter]* viscosityCoefficient * massSquared*kernel.secondDerivative(dist);
		}
	}

}


//其实这里的绑定执行一次就可以了?????????
SphSystemData2Ptr& SphSystemSolver2::sphSystemData()
{

	_sphSystemData->forces() = _particleSystemData->forces();
	_sphSystemData->positions() = _particleSystemData->positions();
	_sphSystemData->velocities() = _particleSystemData->velocities();
	_sphSystemData->numberOfAllParticles() = _particleSystemData->numberOfAllParticles();
	_sphSystemData->neighbor = _particleSystemData->neighbor;
	_sphSystemData->numberOfParticles() = _particleSystemData->numberOfParticles();
	return _sphSystemData;
}


BoundaryPtr& SphSystemSolver2::BoundarySystem()
{
	return _boundary;
}


void SphSystemSolver2::To_Updata_Move_Boundary()
{
	auto& particles = sphSystemData();
	auto x = particles->positions();
	auto allNumber = particles->numberOfAllParticles();
	auto fluidNumber = particles->numberOfParticles();
	auto boundaryPosition = _boundary->BoundaryParticle()->BoundaryPosition();
	int boundaryIndex;
	
	for (int i = fluidNumber; i < allNumber; i++)
	{
		boundaryIndex = i- fluidNumber;
		(*x)[i]=(*boundaryPosition)[boundaryIndex];
	}

}