#ifndef CONSTVAR_H
#define CONSTVAR_H

#include "vector2.h"

//--------const常量

const double kPiD = 3.14159265358979323846264338327950288;
//const double PI = 3.1415936;
const Vector2 GRAVITY(0.0, -9.8);
//------------------PBF粒子半径---------------------------------
//const double R = 0.3;

//----------------粒子半径---------------------------------------
const double R = 0.06;


//----------------PBF核半径---------------------------------
//const double kernelRadius =1.1;

//---------------核半径--------------
const double kernelRadius = 0.06;
//---------------PBF邻居--------------------------
//const double neighbor_radius = kernelRadius * 1.05;

//----------------邻居----------------------
const double neighbor_radius = 0.06;

//----------------粒子重量------------------------------------
const double _mass = 1.0;

//------------------粘度系数？？？？？？？---------------------
const double viscosityCoefficient = 100;


//---------------------声速------------------------------
const double _speedOfSound = 0.0065;

const double _eosExponent = 2.0;

const double _targetDensity = 1.0;

//------------------------速度方向的速度衰减----
const double dragCoefficient =4.0;

//--------------------边界点坐标---------------
Vector2 leftTop(0.015, 1.975);
Vector2 leftDown(0.015, 0.015);
//Vector2 rightTop(1.975, 1.975);
//Vector2 rightDown(1.975, 0.015);
//Vector2 skewLineUp(0.75, 0.75);
//Vector2 skewLinedown(0.5, 0.5);

//---------------------静止密度--------
const double rest_density = 1.099;

//----------------------位置修正参数---
const double corr_deltaQ_coeff = 0.3;
const double corrk = 0.001;

//-----------松弛参数------------
//const double epsilon = 1e-5;
const double epsilon = 1.0;
const double lambda_epsilon = 100.0;


//对于SPH
//窗口大小 200*200；
//粒子坐标范围（0，2）*（0，2）
//网格分辨率（20*20）
//粒子半径R和kernel半径一样的值
//更新密度场为0，设为0.1；


//因为不知道边界中的density_0_i代表的是什么，暂时理解为固、液静止时，液体的密度

const double boundary_density = 3000;


//---------------移动边界需要的位置变化
const double move_boundary = 0.030;



#endif