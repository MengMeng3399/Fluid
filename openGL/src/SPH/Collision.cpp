#include "Collision.h"

Collision::Collision() {

}

Collision::~Collision() {

}

//给一个向量和一个单位向量,返回该向量在单位向量的投影
void Collision::resolveCollision(Vector2& position, Vector2& velocity,double timeIntervalInSeconds,Vector2 boundaryTop,Vector2 boundaryDown) {
	//注意这里点的坐标的问题
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

	//随机数
	auto randomNumber = (rand() % 800) * 0.0001;
	//Edge2 skewLine(skewLineUp, skewLinedown);


	//------------------失败的边界处理-----------------------
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

	//	////垂直于边界的速度分量设为0；
	//	//velocity=velocity- velocityProject1;

	//	//垂直于边界的速度分量有一个衰减。
	//	velocity.x() = -restitutionCoefficient* velocity.x();

	//	//位置更新为边界上的一点
	//	auto temp1 = leftY.pointCoordinateCut(position);
	//	auto temp2 = leftY.Projectionto_Line(temp1);
	//	position = leftY.pointCoordinateAdd(temp2);
	//	position.x() += R;
	//}

	//if (rightY.distanceToPoint(position) <= dist2+R ) {
	//	//velocity = velocity - velocityProject2;

	//	//垂直于边界的速度分量有一个衰减。
	//	auto tempvelocity = -restitutionCoefficient * velocity.x();
	//	velocity.x() = tempvelocity;

	//	//位置更新为边界上的一点
	//	auto temp1 = rightY.pointCoordinateCut(position);
	//	auto temp2 = rightY.Projectionto_Line(temp1);
	//	position = rightY.pointCoordinateAdd(temp2);
	//	position.x() -= R;
	//}

	//if (downX.distanceToPoint(position) <= dist3+R )
 //   {
	//	//velocity = velocity - velocityProject3;

	//	//垂直于边界的速度分量有一个衰减。
	//	velocity.y() = -restitutionCoefficient * velocity.y();

	//	//位置更新为边界上的一点
	//	auto temp1 = downX.pointCoordinateCut(position);
	//	auto temp2 = downX.Projectionto_Line(temp1);
	//	position = downX.pointCoordinateAdd(temp2);
	//	position.y() += R;
	//}

	//if (skewLine.distanceToPoint(position) <= skewdist )
	//{
	//	//判断是在线段范围的边界，（不是直线范围的边界）
	//	auto ifExist = skewLine.ifExist(position);
	//	if (ifExist)
	//	{
	//		velocity = velocity - skewvelocityProject;
	//		cout << "发生了碰撞" << endl;
	//		//state = true;
	//		//位置更新为边界上的一点
	//		auto temp1 = skewLine.pointCoordinateCut(position);
	//		auto temp2 = skewLine.Projectionto_Line(temp1);
	//		position = skewLine.pointCoordinateAdd(temp2);
	//	}
	//}



	//------------------不知道能不能成功的边界处理-------------------

	//------------------人为手动的规定法线-后期完善--------------
	leftY.TargetNormal() = Vector2(1.0,0.0);
	rightY.TargetNormal() = Vector2(-1.0, 0.0);
	downX.TargetNormal() = Vector2(0.0, 1.0);


	auto leftYnormal = leftY.TargetNormal();
	auto rightYnormal = rightY.TargetNormal();
	auto downXnormal = downX.TargetNormal();

	//---判断是否正在逃离---速度和法线的夹角为钝角 
	if (velocity.dot(leftYnormal) < 0.0)
	{ 
		auto closest = leftY.closestPoint(position);
		auto relativePosition = position - closest;
		//-----判断该点位置是否已越界---
		if (relativePosition.dot(leftYnormal) < 0.0)
		{
			position = closest;
			position.x() += randomNumber;
		//	position.x() += 0.05;
			//只保留平行于边界的速度。
			velocity = leftY.Projectionto_Line(velocity);
			velocity = velocity*coffient;
		}
	}



	if (velocity.dot(downXnormal) < 0.0)
	{
		auto closest = downX.closestPoint(position);
		auto relativePosition = position - closest;
		//-----判断该点位置是否已越界---
		if (relativePosition.dot(downXnormal) < 0.0)
		{
			position = closest;
			position.y() += randomNumber;
		//	position.y() += 0.05;
			//只保留平行于边界的速度。
			velocity = downX.Projectionto_Line(velocity);
			velocity = velocity * coffient;
		}
	}

	if (velocity.dot(rightYnormal) < 0.0)
	{
		auto closest = rightY.closestPoint(position);
		auto relativePosition = position - closest;
		//-----判断该点位置是否已越界---
		if (relativePosition.dot(rightYnormal) < 0.0)
		{
			position = closest;
			position.x() -= randomNumber;
			//只保留平行于边界的速度。
			velocity = rightY.Projectionto_Line(velocity);
			velocity.x() = velocity.x() - 2.5;
		}

		
	}
	
}  