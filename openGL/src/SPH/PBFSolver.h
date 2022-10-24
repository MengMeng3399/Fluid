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

	//提供类外函数访问数据
	PBFData2Ptr& PBFdata();

private:
	//引入重力
	void accumulateForces();
	//初步预测位置
	void predictPositions(double timeStepInSeconds);
	//寻找邻居(使用初步预测的位置)并且更新密度
	//void FindNeibor();
	//计算lambda
	void computer_lambda();
	//计算修正值
	void computer_x_delta();
	//处理碰撞
	void resolveCollision();
	//更新位置和速度
	void endAdvanceTimeStep(double timeStepInSeconds);
	
	//附加，对修正值的修正
	double compute_scorr(double r);

	PBFData2Ptr PBFData;
	NeighborSearcher2Ptr neighbor;
	PBF_Collision pbf_collision;


};


#endif