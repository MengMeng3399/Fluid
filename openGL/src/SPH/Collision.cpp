#include "Collision.h"

Collision::Collision() {

}

Collision::~Collision() {

}

//��һ��������һ����λ����,���ظ������ڵ�λ������ͶӰ
void Collision::resolveCollision(Vector2& position, Vector2& velocity,double timeIntervalInSeconds,Vector2 boundaryTop,Vector2 boundaryDown) {
	//ע�����������������
	//Vector2 leftTop(0.0, 1.0);
	//Vector2 leftDown(0.0, 0.0);
	//Vector2 rightTop(1.0, 1.0);
	//Vector2 rightDown(1.0, 0.0);
	//Vector2 skewLineUp(0.75, 0.75);
	//Vector2 skewLinedown(0.5, 0.5);

	Edge2 leftY(leftTop, leftDown);
	Edge2 rightY(boundaryTop, boundaryDown);
	Edge2 downX(leftDown, boundaryDown);
	double coffient = 0.22;

	//�����
	auto randomNumber = (rand() % 800) * 0.0001;
	//Edge2 skewLine(skewLineUp, skewLinedown);


	//------------------ʧ�ܵı߽紦��-----------------------
	//double r = 0.005;
	//auto velocityproject1 = leftY.ProjectiontoLine(velocity);
	//auto velocityproject2 = rightY.ProjectiontoLine(velocity);
	//auto velocityproject3 = downX.ProjectiontoLine(velocity);
	//auto dist1 = (velocityproject1 * timeIntervalInSeconds).getLength();
	//auto dist2 = (velocityproject2 * timeIntervalInSeconds).getLength();
	//auto dist3 = (velocityproject3 * timeIntervalInSeconds).getLength();
	//auto skewvelocityProject = skewLine.ProjectiontoLine(velocity);
	//auto skewdist= (skewvelocityProject * timeIntervalInSeconds).getLength();

	//if (leftY.distanceToPoint(position) <= dist1+R) {

	//	////��ֱ�ڱ߽���ٶȷ�����Ϊ0��
	//	//velocity=velocity- velocityProject1;

	//	//��ֱ�ڱ߽���ٶȷ�����һ��˥����
	//	velocity.x() = -restitutionCoefficient* velocity.x();

	//	//λ�ø���Ϊ�߽��ϵ�һ��
	//	auto temp1 = leftY.pointCoordinateCut(position);
	//	auto temp2 = leftY.Projectionto_Line(temp1);
	//	position = leftY.pointCoordinateAdd(temp2);
	//	position.x() += R;
	//}

	//if (rightY.distanceToPoint(position) <= dist2+R ) {
	//	//velocity = velocity - velocityProject2;

	//	//��ֱ�ڱ߽���ٶȷ�����һ��˥����
	//	auto tempvelocity = -restitutionCoefficient * velocity.x();
	//	velocity.x() = tempvelocity;

	//	//λ�ø���Ϊ�߽��ϵ�һ��
	//	auto temp1 = rightY.pointCoordinateCut(position);
	//	auto temp2 = rightY.Projectionto_Line(temp1);
	//	position = rightY.pointCoordinateAdd(temp2);
	//	position.x() -= R;
	//}

	//if (downX.distanceToPoint(position) <= dist3+R )
 //   {
	//	//velocity = velocity - velocityProject3;

	//	//��ֱ�ڱ߽���ٶȷ�����һ��˥����
	//	velocity.y() = -restitutionCoefficient * velocity.y();

	//	//λ�ø���Ϊ�߽��ϵ�һ��
	//	auto temp1 = downX.pointCoordinateCut(position);
	//	auto temp2 = downX.Projectionto_Line(temp1);
	//	position = downX.pointCoordinateAdd(temp2);
	//	position.y() += R;
	//}

	//if (skewLine.distanceToPoint(position) <= skewdist )
	//{
	//	//�ж������߶η�Χ�ı߽磬������ֱ�߷�Χ�ı߽磩
	//	auto ifExist = skewLine.ifExist(position);
	//	if (ifExist)
	//	{
	//		velocity = velocity - skewvelocityProject;
	//		cout << "��������ײ" << endl;
	//		//state = true;
	//		//λ�ø���Ϊ�߽��ϵ�һ��
	//		auto temp1 = skewLine.pointCoordinateCut(position);
	//		auto temp2 = skewLine.Projectionto_Line(temp1);
	//		position = skewLine.pointCoordinateAdd(temp2);
	//	}
	//}



	//------------------��֪���ܲ��ܳɹ��ı߽紦��-------------------

	//------------------��Ϊ�ֶ��Ĺ涨����-��������--------------
	leftY.TargetNormal() = Vector2(1.0,0.0);
	rightY.TargetNormal() = Vector2(-1.0, 0.0);
	downX.TargetNormal() = Vector2(0.0, 1.0);


	auto leftYnormal = leftY.TargetNormal();
	auto rightYnormal = rightY.TargetNormal();
	auto downXnormal = downX.TargetNormal();

	//---�ж��Ƿ���������---�ٶȺͷ��ߵļн�Ϊ�۽� 
	if (velocity.dot(leftYnormal) < 0.0)
	{ 
		auto closest = leftY.closestPoint(position);
		auto relativePosition = position - closest;
		//-----�жϸõ�λ���Ƿ���Խ��---
		if (relativePosition.dot(leftYnormal) < 0.0)
		{
			position = closest;
			position.x() += randomNumber;
		//	position.x() += 0.05;
			//ֻ����ƽ���ڱ߽���ٶȡ�
			velocity = leftY.Projectionto_Line(velocity);
			velocity = velocity*coffient;
		}
	}



	if (velocity.dot(downXnormal) < 0.0)
	{
		auto closest = downX.closestPoint(position);
		auto relativePosition = position - closest;
		//-----�жϸõ�λ���Ƿ���Խ��---
		if (relativePosition.dot(downXnormal) < 0.0)
		{
			position = closest;
			position.y() += randomNumber;
		//	position.y() += 0.05;
			//ֻ����ƽ���ڱ߽���ٶȡ�
			velocity = downX.Projectionto_Line(velocity);
			velocity = velocity * coffient;
		}
	}

	if (velocity.dot(rightYnormal) < 0.0)
	{
		auto closest = rightY.closestPoint(position);
		auto relativePosition = position - closest;
		//-----�жϸõ�λ���Ƿ���Խ��---
		if (relativePosition.dot(rightYnormal) < 0.0)
		{
			position = closest;
			position.x() -= randomNumber;
			//ֻ����ƽ���ڱ߽���ٶȡ�
			velocity = rightY.Projectionto_Line(velocity);
			velocity.x() = velocity.x() - 2.5;
		}

		
	}
	
}  