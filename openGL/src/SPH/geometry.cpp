#include "geometry.h"

Edge2::Edge2() {

}

Edge2::~Edge2() {

}

Edge2::Edge2(const Vector2& p1, const Vector2& p2) :_p1(p1), _p2(p2) {


}
//返回点到线段的距离 _p1和_p2为给定线段（即边界）的端点，p为粒子
double Edge2::distanceToPoint(const Vector2& p)const {
	auto pp1 = _p1 - p;
	auto pp2 = _p2 - p;
	auto p1p2 = _p2 - _p1;
	auto k = abs(pp1.cross(pp2)) / 2;
	auto p1p2Len = p1p2.getLength();
	auto dis = k / p1p2Len;
	return dis;
}

Vector2 Edge2::Projection(const Vector2& temp, const Vector2& direction)
{
	//double cosAngle = temp.dot(direction)/temp.getLength();
	//auto tempVector = direction*temp.getLength() * cosAngle;
	auto tempVector = direction * (direction.dot(temp));
	return tempVector;
}


Vector2 Edge2::ProjectiontoLine(const Vector2& temp)
{
	auto direction = (_p1 - _p2).normalize();

	auto tempVector= Projection(temp, direction);

	//返回实际需要的分量；
	return temp - tempVector;
}


Vector2  Edge2::pointCoordinateAdd(const Vector2& temp)
{
	return temp +_p2;
}

Vector2  Edge2::pointCoordinateCut(const Vector2& temp)
{
	return temp - _p2;
}


bool Edge2::ifExist(const Vector2 temp)
{
	auto firstdot = (temp - _p1).dot(_p2 - _p1);
	auto seconddot = (temp - _p2).dot(_p1 - _p2);
	if ((firstdot * seconddot) <=0.0)
	{
		return false;
	}
	else
	{
		return true;
	}
}


Vector2 Edge2::Projectionto_Line(const Vector2& temp)
{
	auto direction = (_p1 - _p2).normalize();

	auto tempVector = Projection(temp, direction);
	
	return tempVector;
}


Vector2& Edge2::TargetNormal()
{
   
	return targetNormal;
}


Vector2 Edge2::closestPoint(Vector2 point)
{
	auto n = (_p1 - _p2).normalize();
	auto p = point - _p2;
	auto projectToN = n*(n.dot(p));
	return projectToN + _p2;
}