#include"Versatile Rigid-fluid Coupling.h"

Boundary::Boundary()
{
	boundaryParticle = make_shared<BoundaryParticleData2>();
	
}

Boundary::~Boundary()
{

}

void  Boundary::setData(int numberOfBoundaryParticles,Vector2ArrayPtr boundaryPosition,int resolutionX, int resolutionY)
{
	boundaryParticle->numberOfBoundaryParticles() = numberOfBoundaryParticles;
	boundaryParticle->BoundaryPosition() = boundaryPosition;

	//��ʼ���������Ϊ�����±긳ֵ��
	vector<double> temp(numberOfBoundaryParticles, 0.0);
	boundaryParticle->BoundaryVolunm() = make_shared<DoubleArray>(temp);
	//����ʱ���������ӵ��ھ����������ܻ������
	boundaryParticle->neighbor=make_shared<NeighborSearcher2>(resolutionX, resolutionY, numberOfBoundaryParticles);
	boundaryParticle->neighbor->setNeiborList(boundaryParticle->BoundaryPosition());
}




void Boundary::boundPointVolunm()
{  
	//���ֻ����һ�Σ���Ϊ�õ��ǹ̶��߽硣
	auto temp1 = boundaryParticle->neighbor->neighBors();
	auto numberOfParticles = boundaryParticle->numberOfBoundaryParticles();
	auto x = boundaryParticle->BoundaryPosition();
	auto& volunm = boundaryParticle->BoundaryVolunm();
	SphSpikyKernel2 kernel(kernelRadius);
	double sum;

	//��֪�������ﰴ���ĸ��˺������µ����������ʱ����SphSpikyKernel��Ч�������ٻ���

	for (int i = 0; i < numberOfParticles; i++)
	{  
		sum = 0.0;
		auto temp2 = temp1[i];
		for (auto iter = temp2.begin(); iter != temp2.end(); iter++)
		{
			double dist = (x->lookAt(i)).dis(x->lookAt(*iter)); //����
			sum += kernel(dist);
		}
		(*volunm)[i] = 1.0 / sum;
	}
}

BoundaryParticleData2Ptr& Boundary::BoundaryParticle()
{
	return boundaryParticle;
}

//----------------��дһ���߽�Ƚϼ򵥵ı仯---------------------------
void Boundary:: Upadate_Move_Boundary(int numberOfMoveBoundary)
{
	auto& position = BoundaryParticle()->BoundaryPosition();
	
	if ((*position)[0].x() < 0.50 || (*position)[0].x() > 1.50)
	{
		ifover = -ifover;
	}

	for (int i = 0; i < numberOfMoveBoundary; i++)
	{

		(*position)[i].x() = (*position)[i].x() + ifover * move_boundary;
	}

}