#ifndef COLLISION_H
#define COLLISION_H

#include "Vector2Array.h"
#include "geometry.h"
#include"ConstVar.h"

//------------------------------碰撞处理--------------------------
//暂时先设定碰撞处理为：
//三条边界，对应于opengl窗口的两条y方向边界，和窗口下侧x方向边界
//每个粒子每一时步都要计算与三条边界的距离，如果达到碰撞条件，则作处理

//将速度在边界上的法线分量设为0
class Collision {
public:
	Collision();
	~Collision();

public:
	void resolveCollision(Vector2& position, Vector2& velocity, double timeIntervalInSeconds,Vector2 boundaryTop,Vector2 boundaryDown);
};

#endif
