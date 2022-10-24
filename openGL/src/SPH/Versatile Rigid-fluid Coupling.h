#pragma once
#include "Vector2.h"
#include"Vector2Array.h"
#include"DoubleArray.h"
#include"BoundaryParticleData2.h"
#include"SphSpikyKernel2.h"
#include<math.h>
struct Boundary
{
	//��дһ���̶��߽�
	//�ֶ����ñ߽�Ĳ�����
	//��ʱ�����Ǽ���߽����ӵ����ʱֻ��Ҫ�߽������ھӡ������������壩  

	Boundary();
	~Boundary();
	//���ñ߽��λ��
	void  setData(int numberOfBoundaryParticles,Vector2ArrayPtr boundaryPositionint,int resolutionX, int resolutionY);
	//����߽����ӵ����,��Ҫ��ǰ���ӵ��ھ�
	void boundPointVolunm();

	BoundaryParticleData2Ptr& BoundaryParticle();

private:
	BoundaryParticleData2Ptr boundaryParticle;
	int ifover = -1;
	//�������ƶ��߽磬�ƶ��߽���Ҫ����λ�á�
public:
	void Upadate_Move_Boundary(int numberOfMoveBoundary);

};

using BoundaryPtr = shared_ptr<Boundary>;