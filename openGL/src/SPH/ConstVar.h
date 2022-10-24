#ifndef CONSTVAR_H
#define CONSTVAR_H

#include "vector2.h"

//--------const����

const double kPiD = 3.14159265358979323846264338327950288;
//const double PI = 3.1415936;
const Vector2 GRAVITY(0.0, -9.8);
//------------------PBF���Ӱ뾶---------------------------------
//const double R = 0.3;

//----------------���Ӱ뾶---------------------------------------
const double R = 0.06;


//----------------PBF�˰뾶---------------------------------
//const double kernelRadius =1.1;

//---------------�˰뾶--------------
const double kernelRadius = 0.06;
//---------------PBF�ھ�--------------------------
//const double neighbor_radius = kernelRadius * 1.05;

//----------------�ھ�----------------------
const double neighbor_radius = 0.06;

//----------------��������------------------------------------
const double _mass = 1.0;

//------------------ճ��ϵ����������������---------------------
const double viscosityCoefficient = 100;


//---------------------����------------------------------
const double _speedOfSound = 0.0065;

const double _eosExponent = 2.0;

const double _targetDensity = 1.0;

//------------------------�ٶȷ�����ٶ�˥��----
const double dragCoefficient =4.0;

//--------------------�߽������---------------
Vector2 leftTop(0.015, 1.975);
Vector2 leftDown(0.015, 0.015);
//Vector2 rightTop(1.975, 1.975);
//Vector2 rightDown(1.975, 0.015);
//Vector2 skewLineUp(0.75, 0.75);
//Vector2 skewLinedown(0.5, 0.5);

//---------------------��ֹ�ܶ�--------
const double rest_density = 1.099;

//----------------------λ����������---
const double corr_deltaQ_coeff = 0.3;
const double corrk = 0.001;

//-----------�ɳڲ���------------
//const double epsilon = 1e-5;
const double epsilon = 1.0;
const double lambda_epsilon = 100.0;


//����SPH
//���ڴ�С 200*200��
//�������귶Χ��0��2��*��0��2��
//����ֱ��ʣ�20*20��
//���Ӱ뾶R��kernel�뾶һ����ֵ
//�����ܶȳ�Ϊ0����Ϊ0.1��


//��Ϊ��֪���߽��е�density_0_i�������ʲô����ʱ���Ϊ�̡�Һ��ֹʱ��Һ����ܶ�

const double boundary_density = 3000;


//---------------�ƶ��߽���Ҫ��λ�ñ仯
const double move_boundary = 0.030;



#endif