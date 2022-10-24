#ifndef PBF_COLLISION_H
#define PBF_COLLISION_H

#include "Vector2Array.h"
#include "geometry.h"
#include"ConstVar.h"

//------------------------------碰撞处理--------------------------
//暂时先设定碰撞处理为：
//三条边界，对应于opengl窗口的两条y方向边界，和窗口下侧x方向边界

class PBF_Collision {
public:
	PBF_Collision();
	~PBF_Collision();

public:
	void resolveCollision(Vector2& position);

private:
	//先写一个固定边界
	double x_min = 1.0;
	double x_max =79.0;
	double y_min = 1.0;
	double y_max = 49.0;
};

#endif

