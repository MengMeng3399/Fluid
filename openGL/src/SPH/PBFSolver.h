#ifndef PBFSOLVER_H
#define PBFSOLVER_H

#include <iostream>
#include"Vector2Array.h"
#include"ConstVar.h"
#include"DoubleArray.h"
#include"Spiky.h"
#include"poly_6.h"
#include"SphSystemData2.h"
#include"PBFData2.h"
#include"PBF_Collision.h"

using namespace std;

class PBFSolver
{
public:
	PBFSolver();
	~PBFSolver();

	void setData(int numberOfParticles, Vector2ArrayPtr pos,
		int resolutionX, int resolutionY);
	void onAdvanceTimeStep(double timeStepInSeconds);

	//�ṩ���⺯����������
	PBFData2Ptr& PBFdata();

private:
	//��������
	void accumulateForces();
	//����Ԥ��λ��
	void predictPositions(double timeStepInSeconds);
	//Ѱ���ھ�(ʹ�ó���Ԥ���λ��)���Ҹ����ܶ�
	//void FindNeibor();
	//����lambda
	void computer_lambda();
	//��������ֵ
	void computer_x_delta();
	//������ײ
	void resolveCollision();
	//����λ�ú��ٶ�
	void endAdvanceTimeStep(double timeStepInSeconds);
	
	//���ӣ�������ֵ������
	double compute_scorr(double r);

	PBFData2Ptr PBFData;
	NeighborSearcher2Ptr neighbor;
	PBF_Collision pbf_collision;


};


#endif