#ifndef COLLISION_H
#define COLLISION_H

#include "Vector2Array.h"
#include "geometry.h"
#include"ConstVar.h"

//------------------------------��ײ����--------------------------
//��ʱ���趨��ײ����Ϊ��
//�����߽磬��Ӧ��opengl���ڵ�����y����߽磬�ʹ����²�x����߽�
//ÿ������ÿһʱ����Ҫ�����������߽�ľ��룬����ﵽ��ײ��������������

//���ٶ��ڱ߽��ϵķ��߷�����Ϊ0
class Collision {
public:
	Collision();
	~Collision();

public:
	void resolveCollision(Vector2& position, Vector2& velocity, double timeIntervalInSeconds,Vector2 boundaryTop,Vector2 boundaryDown);
};

#endif
