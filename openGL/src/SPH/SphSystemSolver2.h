#ifndef SPHSYSTEMSOLVER2_H
#define SPHSYSTEMSOLVER2_H

#include "ParticleSystemSolver2.h"
#include"SphSystemData2.h"
#include"DoubleArray.h"
#include"Vector2Array.h"
#include"SphStdKernel2.h"
#include"SphSpikyKernel2.h"
#include"Versatile Rigid-fluid Coupling.h"

class SphSystemSolver2 : public ParticleSystemSolver2 {
public:
	SphSystemSolver2();
	~SphSystemSolver2();
	void setData(int numberOfParticles,int numberOfAllarticles, Vector2ArrayPtr pos,
		         int resolutionX, int resolutionY);
	virtual void onAdvanceTimeStep(double timeStepInSeconds,Vector2 boundaryTop, Vector2 boundaryDown)override;
	//�����õ���ǿ������ת�����ѻ���ǿ��ת��Ϊ������
	//��û������dynamic_pointer_cast���÷������Ҳ���
	SphSystemData2Ptr& sphSystemData();
	BoundaryPtr& BoundarySystem();
protected:

	void accumulateForces(double timeStepInSeconds)override;

	void beginAdvanceTimeStep();
	//�����ѹ�����������������������ճ��������αճ��������
	virtual void accumulateNonPressureForce(double timeStepInSeconds);
	//����ѹ�����������������ѹ��
	virtual void accumulatePressureForce(double timeStepInSeconds);
	//��Ч�����������,���pressure[],Ϊ��������-----------------------------------------------;
	void computePressure();
	//״̬���̣�����prssure
	double computerPressureFromEos(double density, double targetDensity, double eosScale, 
		                            double eosExponent,double negativePressureScale);
	//ճ������
	void accumulateViscosityForce();
	//αճ������,δʵ��
	void computePseudoViscosity();
	//����accumulatePressureForce������ѹ����
	void accumulatePressureForce(Vector2ArrayPtr pos, DoubleArrayPtr densities, DoubleArrayPtr pressure, Vector2ArrayPtr forces);
	//��������ɵı߽��������ϵͳ��
	void To_Updata_Move_Boundary();
private:
	SphSystemData2Ptr _sphSystemData;


	//�Է��߽紦���������Ϊ�߽紦����Ҫ�����ݡ�
	//�������룺�����ھ�ʱ��Ҫ�����߽磬���Խ�����������߽����Ӵ洢��һ���ȷ������ű߽硣

	BoundaryPtr _boundary;
};

#endif