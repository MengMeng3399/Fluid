#include"PBF_Collision.h"


PBF_Collision::PBF_Collision()
{

}
PBF_Collision::~PBF_Collision()
{

}

void PBF_Collision::resolveCollision(Vector2& position)
{

	//ʹ������������������
	//������������̫�ã�α�������������


	//  /* ��� 0 �� 49 ֮��� 5 ������� */
	//for (i = 0; i < n; i++) {
	//	printf("%d\n", rand() % 50);
	//}


	//auto randomNumber = (rand() % 1000) * 0.001;
	auto randomNumber = (rand() % 20)*0.01 ;
	//auto randomNumber = 2.0;

	if (position.x() <= x_min)
	{
		position.x() = x_min + epsilon * randomNumber;

		//position.x() = x_min;
	}

	if (position.x() >= x_max)
	{
		position.x() = x_max - epsilon * randomNumber;
		//position.x() = x_max;
	}
	if (position.y() <= y_min)
	{
		position.y() = y_min + epsilon * randomNumber;
	//	position.x() = position.x() + epsilon * 10.0;
		//position.y() = y_min;
	}

	if (position.y() >= y_max)
	{
		position.y() = y_max - epsilon * randomNumber;
	//	position.x() = position.x() + epsilon * 10.0;
		//position.y() = y_max;
	}

}