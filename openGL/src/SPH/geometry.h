#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vector2.h"
#include <cmath>
#include<iostream>

using namespace std;

//�����ж����ӵ��߶Σ������߽磩�ľ���
//�ȼ򵥵�дһ����ά�߶ε�geometry
class Edge2 {
public:
	Edge2();
	Edge2(const Vector2& p1, const Vector2& p2);
	~Edge2();

	double distanceToPoint(const Vector2& p)const;
	Vector2 Projection(const Vector2& temp, const Vector2& direction);
	Vector2 ProjectiontoLine(const Vector2& temp);

	//��߽����������_p2��
	Vector2 pointCoordinateAdd(const Vector2& temp);
	//��߽��������--_p2��
	Vector2 pointCoordinateCut(const Vector2& temp);

	//�жϸõ������߶η�Χ�ڣ�����ֱ�߷�Χ�ڣ�
	bool ifExist(const Vector2 temp);

	//���������ڸ��������ͶӰ
	Vector2 Projectionto_Line(const Vector2& temp);

	//�涨�߽���ĳһ��ķ���
	Vector2 &TargetNormal();

	//���ر߽��Ͼ���õ�����ĵ�
	Vector2  closestPoint(Vector2 point);

	
	

private:
	Vector2 _p1;
	Vector2 _p2;
	Vector2 targetNormal;
};

#endif
