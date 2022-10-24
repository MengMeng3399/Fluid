#include"PBFSolver.h"


PBFSolver::PBFSolver()
{
	PBFData = make_shared<PBFData2>();
}
PBFSolver::~PBFSolver()
{

}

void PBFSolver::setData(int numberOfParticles, Vector2ArrayPtr pos,
	int resolutionX, int resolutionY)

{  //��ֵ�����������ӵĳ�ʼλ��
	PBFData->numberOfParticles() = numberOfParticles;
	PBFData->positions() = pos;

	//��ʼ���ܶȣ�lambda
	vector<double> temp(numberOfParticles, 0.0);
	PBFData->densities() = make_shared<DoubleArray>(temp);
	PBFData->lambda() = make_shared<DoubleArray>(temp);

	//��ʼ���ٶȣ�Ԥ��λ�ã�����x_delta;
	vector<Vector2> tempV;
	for (int i = 0; i < numberOfParticles; ++i)
	{
		Vector2 v;
		tempV.push_back(v);

	}
	PBFData->velocities() = make_shared<Vector2Array>(tempV);
	PBFData->predict_position()= make_shared<Vector2Array>(tempV);
	PBFData->x_delta()= make_shared<Vector2Array>(tempV);
	PBFData->forces() = make_shared<Vector2Array>(tempV);

	//��ʼ�ھ�
	PBFData->neighbor = make_shared<NeighborSearcher2>(resolutionX, resolutionY, numberOfParticles);
}

void PBFSolver::onAdvanceTimeStep(double timeStepInSeconds)
{
	//��������
    accumulateForces();
	//����Ԥ��λ��
	predictPositions(timeStepInSeconds);
	//Ѱ���ھ�(ʹ�ó���Ԥ���λ��)���Ҹ����ܶȡ�
	// FindNeibor();
	//����lambda
	 for (int i = 0; i < 5; i++)
	 {
		 computer_lambda();
		 //��������ֵ
		 computer_x_delta();
		 //������ײ
	 }
	 resolveCollision();
	//����λ�ã��ٶ�
	 endAdvanceTimeStep(timeStepInSeconds);
	 
}


void PBFSolver::accumulateForces()
{
	size_t n = PBFData->numberOfParticles();
	auto forces = PBFData->forces();

	for (size_t i = 0; i < n; ++i) {
		auto force = GRAVITY * _mass;
		(*forces)[i] = force;
	
	}
}

void PBFSolver::predictPositions(double timeStepInSeconds)
{
	size_t n = PBFData->numberOfParticles();
	auto forces = PBFData->forces();
	auto velocities = PBFData->velocities();
	auto positions = PBFData->positions();
	auto predictPosition = PBFData->predict_position();
	//Ԥ��λ��
	for (int i = 0; i < n; i++)
	{
		auto temp1 = (*velocities)[i] + ((*forces)[i] / _mass) * timeStepInSeconds;
		auto temp2 = (*positions)[i] + temp1 * timeStepInSeconds;
		(*predictPosition)[i] = temp2;
	}
	////����Ԥ��λ���Ƿ�ɹ�
	//for (int i = 0; i < n; i++)
	//{
	//	cout << "������Ԥ��λ��" << endl;
	//	cout << (*predictPosition)[i].y() << endl;
	//	cout << "��������һ��λ��" << endl;
	//	cout << (*positions)[i].y() << endl;
	//}
}

//void PBFSolver::FindNeibor()
//{
//	PBFData->neighbor->setNeiborList(PBFData->predict_position());
//
//	PBFData->updateDensities();
//}


void PBFSolver::computer_lambda()
{

	size_t n = PBFData->numberOfParticles();
	auto pre_positions = PBFData->predict_position();
	PBFData->neighbor->setNeiborList(pre_positions);
	auto neibors = PBFData->neighbor->neighBors();
	auto densities = PBFData->densities();
	auto lambdas = PBFData->lambda();
	Vector2 grad_i, grad_j;
	double sum_grad_sqr;
	Spiky kernel(kernelRadius);
	Poly_6 den_kernel(kernelRadius);

	//���������ܶȵĸ����� ���ﲻ��Ҫ�ڼ����ܶ��ˡ�
   //SphStdKernel2 den_kernel(kernelRadius);
	
	for (int i = 0; i < n; i++)
	{
		auto temp2 = neibors[i];
		grad_i = Vector2(0.0, 0.0);
		sum_grad_sqr = 0.0;
		auto density_constraint = 0.0;
		for (auto iter = temp2.begin(); iter != temp2.end(); iter++)
		{
			double dist = (pre_positions->lookAt(i)).dis(pre_positions->lookAt(*iter));   //����
			if (dist > 0.0)
			{
				grad_j = Vector2(0.0, 0.0);
				Vector2 dir = (pre_positions->lookAt(i)).direct(pre_positions->lookAt(*iter));  //����
				grad_j = kernel.gradent(dist, dir);
				grad_i = grad_i+grad_j;
				sum_grad_sqr += grad_j.dot(grad_j);
				//(*densities)[i] = (*densities)[i] + den_kernel(dist);
				density_constraint += den_kernel(dist);
			}
		}
		(*densities)[i]= density_constraint;
		density_constraint = (_mass*density_constraint / rest_density)-1.0;
		sum_grad_sqr += grad_i.dot(grad_i);
		(*lambdas)[i] = -(density_constraint) / (sum_grad_sqr+lambda_epsilon);
	}
	
}

//���ӣ�������ֵ������
double PBFSolver::compute_scorr(double r)
{
	Poly_6 kernel(kernelRadius);
	auto x = kernel(r) / kernel(corr_deltaQ_coeff * kernelRadius);
	x = x * x * x * x;
	return (-corrk) * x;
}


void PBFSolver::computer_x_delta()
{
	size_t n = PBFData->numberOfParticles();
	auto pre_positions = PBFData->predict_position();
	auto neibors = PBFData->neighbor->neighBors();
	auto lambdas = PBFData->lambda();
	auto x_deltas = PBFData->x_delta();
	Spiky kernel(kernelRadius);
	double scorr_ij;
	for (int i = 0; i < n; i++)
	{
		auto temp2 = neibors[i];
		for (auto iter = temp2.begin(); iter != temp2.end(); iter++)
		{
			double dist = (pre_positions->lookAt(i)).dis(pre_positions->lookAt(*iter));   //����
			if (dist > 0.0)
			{
				scorr_ij = compute_scorr(dist);
				Vector2 dir = (pre_positions->lookAt(i)).direct(pre_positions->lookAt(*iter));  //����
				(*x_deltas)[i] = (*x_deltas)[i] + kernel.gradent(dist,dir)* (((*lambdas)[i]) + ((*lambdas)[(*iter)]) + scorr_ij);
			}
		}
		(*x_deltas)[i] = (*x_deltas)[i] / rest_density;
	}

	for (int i = 0; i < n; i++)
	{
		(*pre_positions)[i] = (*pre_positions)[i] + (*x_deltas)[i];
	}

}


void PBFSolver::resolveCollision()
{
	size_t n = PBFData->numberOfParticles();
	auto pre_positions = PBFData->predict_position();
	auto x_deltas = PBFData->x_delta();
	

	for (int i = 0; i < n; i++)
	{
		auto& pre_newPosition = (*pre_positions)[i];

		//pre_newPosition = pre_newPosition + (*x_deltas)[i];

		pbf_collision.resolveCollision(pre_newPosition);
	}
}


void PBFSolver::endAdvanceTimeStep(double timeStepInSeconds)
{
	size_t n = PBFData->numberOfParticles();
	auto pre_positions = PBFData->predict_position();
	auto x_deltas = PBFData->x_delta();
	auto position = PBFData->positions();
	auto velocities = PBFData->velocities();
	for (int i = 0; i < n; i++)
	{
		(*velocities)[i] = ((*pre_positions)[i] - (*position)[i]) / timeStepInSeconds;
	}
	PBFData->positions() = pre_positions;


}

PBFData2Ptr& PBFSolver::PBFdata()
{
	return PBFData;
}

