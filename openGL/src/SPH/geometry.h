#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vector2.h"
#include <cmath>
#include<iostream>

using namespace std;

//可以判断粒子到线段（给定边界）的距离
//先简单的写一个二维线段的geometry
class Edge2 {
public:
	Edge2();
	Edge2(const Vector2& p1, const Vector2& p2);
	~Edge2();

	double distanceToPoint(const Vector2& p)const;
	Vector2 Projection(const Vector2& temp, const Vector2& direction);
	Vector2 ProjectiontoLine(const Vector2& temp);

	//与边界向量相减—_p2；
	Vector2 pointCoordinateAdd(const Vector2& temp);
	//与边界向量相加--_p2；
	Vector2 pointCoordinateCut(const Vector2& temp);

	//判断该点是在线段范围内（不是直线范围内）
	bool ifExist(const Vector2 temp);

	//返回向量在给定方向的投影
	Vector2 Projectionto_Line(const Vector2& temp);

	//规定边界上某一点的法线
	Vector2 &TargetNormal();

	//返回边界上距离该点最近的点
	Vector2  closestPoint(Vector2 point);

	
	

private:
	Vector2 _p1;
	Vector2 _p2;
	Vector2 targetNormal;
};

#endif
