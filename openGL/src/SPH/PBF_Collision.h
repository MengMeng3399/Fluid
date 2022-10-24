#ifndef PBF_COLLISION_H
#define PBF_COLLISION_H

#include "Vector2Array.h"
#include "geometry.h"
#include"ConstVar.h"

//------------------------------��ײ����--------------------------
//��ʱ���趨��ײ����Ϊ��
//�����߽磬��Ӧ��opengl���ڵ�����y����߽磬�ʹ����²�x����߽�

class PBF_Collision {
public:
	PBF_Collision();
	~PBF_Collision();

public:
	void resolveCollision(Vector2& position);

private:
	//��дһ���̶��߽�
	double x_min = 1.0;
	double x_max =79.0;
	double y_min = 1.0;
	double y_max = 49.0;
};

#endif

