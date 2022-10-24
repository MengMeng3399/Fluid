#include <iostream>
using namespace std;

#include <fstream>
#include <string>
#include <vector>
#include "vector2.h"
#include "random.h"
#include "ParticleSystemSolver2.h"
#include"SphSystemSolver2.h"
#include"ConstVar.h"
//#include"PBFData2.h"
//#include"PBFSolver.h"

#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

//��Ļ�ĳ���
const GLuint WIDTH = 400, HEIGHT = 400;

//���̻ص�����
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


//--------------����------------------
void TestPoint(double x, double y)
{
	//��Ĵ�СĬ��Ϊһ�����أ�ͨ������ĺ�����������һ��Ĵ�С
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.5f, 0.2f);
	glVertex2f(x, y);
	glEnd();
}
//----------------���߽�� �ò�ͬ����ɫ-------
void TestBoundaryPoint(double x, double y)
{
	//��Ĵ�СĬ��Ϊһ�����أ�ͨ������ĺ�����������һ��Ĵ�С
	glPointSize(7.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(x, y);
	glEnd();
}




//------------����-------------------

void drawLine(double x1, double y1, double x2, double y2)
{
	glLineWidth(8);//�����߶ο��
	glBegin(GL_LINES);
	glColor3f(0.5, 0.5, 1.0);
	glVertex2f(x1, y1); //�������귶Χ

	glVertex2f(x2, y2);
	glEnd();
}
//����任
Vector2 & toOpenglCoordinate(Vector2 coordinate)
{
	double x = coordinate.x()  - 1.0;
	double y = coordinate.y()  - 1.0;
	auto temp = Vector2(x, y);
	return temp;
}
//-----------------�����߽�-------------
//void drawEdge()
//{
//	auto _leftTop = toOpenglCoordinate(leftTop);
//	auto _leftDown = toOpenglCoordinate(leftDown);
//	auto _rightTop = toOpenglCoordinate(rightTop);
//	auto _rightDown = toOpenglCoordinate(rightDown);
//	//auto _skewLineUp = toOpenglCoordinate(skewLineUp);
//	//auto _skewLinedown = toOpenglCoordinate(skewLinedown);
//
//
//	drawLine(_leftTop.x(), _leftTop.y(), _leftDown.x(), _leftDown.y());
//	drawLine(_rightTop.x(), _rightTop.y(), _rightDown.x(), _rightDown.y());
//	drawLine(_leftDown.x(), _leftDown.y(), _rightDown.x(), _rightDown.y());
////	drawLine(_skewLineUp.x(), _skewLineUp.y(), _skewLinedown.x(), _skewLinedown.y());
//
//}

void drawMoveBoundary(Vector2 down, Vector2 top)
{
	double opengl_X1 = down.x() - 1.0;
	double opengl_Y1 = down.y() - 1.0;

	double opengl_X2 = top.x() - 1.0;
	double opengl_Y2 = top.y() - 1.0;
	drawLine(opengl_X1, opengl_Y1, opengl_X2, opengl_Y2);
}

int main() {

	cout << "Starting GlFW context,OpenGL 3.3" << endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);   //���̻ص�
	//��ʼ��
	glewExperimental = GL_TRUE;
	glewInit();

	int width, height;                                   //���ô��ڵĴ�Сλ��
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	//---------------------
    int resolutionX = 20;
    int resolutionY = 20;

	SphSystemSolver2* solver = new SphSystemSolver2();
	//PBFSolver* solver = new PBFSolver();
	int numberOfParticles = 0;
	int numberOfAllParticles = 0;
	int numberOfMoveBoundary = 0;
    vector<Vector2> tempV1;
	vector<Vector2> tempV2;

  //for (int i = 0; i < numberOfParticles; ++i) 
  // {
  //  double x = random_double(0.45, 0.70);
  //  double y = random_double(0.70, 0.95);

  //  Vector2 v(x, y);
  //  tempV1.push_back(v);

  // }

   //for (double i = 0.01; i < 0.99; i += 0.05) {
	  // for (double j = 0.01; j < 0.3; j += 0.05) {
		 //  Vector2 v(i, j);
		 //  tempV1.push_back(v);
		 //  numberOfParticles++;
	  // }
   //}

  // auto x0 = 0.80;
  // auto y0 = 0.80;
  // auto r = 0.05;
  // auto r_square = r * r;
  //for (double i = 0.75; i < 0.85; i += 0.009) {
	 //  for (double j = 0.75; j < 0.85; j += 0.009) {
		//   
		//   if ((i - x0) * (i - x0) + (j - y0) * (j - y0) <= r_square) {
		//	   Vector2 v(i, j);
		//	   tempV1.push_back(v);
		//	   numberOfParticles++;
		//   }      
	 //  }
  // }

	//---------------PBF��ʼλ��---------------
	//auto x0 = 40.0;
	//auto yo = 10.0;
	//for (double i = 10.0; i < 70; i +=0.8)
	//	for (double j = 0.0; j < 10 ;j += 1.5)
	//	{
	//		Vector2 v(i, j);
	//		tempV1.push_back(v);
	//		numberOfParticles++;
	//	}
 //  cout << numberOfParticles << endl;

//-----------------------------SPH��ʼλ��----------------------------

	for (double i = 0.150; i < 1.30; i += 0.050) {
		for (double j = 0.05; j < 1.20; j += 0.050) {
			Vector2 tempV(i, j);
			tempV1.push_back(tempV);
			numberOfParticles++;
			numberOfAllParticles++;
		}
	}

//-------------------------�߽�ĳ�ʼλ��--------------------------------
	//--------------------����һ���߽�����Ϊ�ƶ��߽�--------------
	for (double i = 0.0; i < 2.0; i += 0.05)
	{
		Vector2 tempV(1.49,i);
		tempV1.push_back(tempV);
		tempV2.push_back(tempV);
		numberOfAllParticles++;
		numberOfMoveBoundary++;
	}
	//--------------------�ڶ����߽� y=0.0��
	for (double i = 0.0; i < 2.0; i += 0.05)
	{
		Vector2 tempV(i, 0.0);
		tempV1.push_back(tempV);
		tempV2.push_back(tempV);
		numberOfAllParticles++;
	}

	//--------------------�������߽� x=0.0��
	for (double i = 0.0; i < 2.0; i += 0.05)
	{
		Vector2 tempV(0.0, i);
		tempV1.push_back(tempV);
		tempV2.push_back(tempV);
		numberOfAllParticles++;
	}

	/*auto r = 0.1;
	auto square_r = r * r;
	auto x0 = 1.0;
	auto y0 = 1.1;
	for (double i = 0.5; i < 1.5; i += 0.035) {
		for (double j = 0.5; j < 1.5; j += 0.035) {
			auto k = (i - x0) * (i - x0) + (j - y0) * (j - y0);
			if (k < square_r) {
				Vector2 tempV(i, j);
				tempV1.push_back(tempV);
				numberOfParticles++;
			}

		}
	}*/
	auto numberOfBoundaryParticles = numberOfAllParticles - numberOfParticles;
	cout << numberOfAllParticles << endl;
    Vector2ArrayPtr beginpos = make_shared<Vector2Array>(tempV1);
	Vector2ArrayPtr boundary_beginpos = make_shared<Vector2Array>(tempV2);
	solver->setData(numberOfParticles, numberOfAllParticles, beginpos, resolutionX, resolutionY);
	solver->BoundarySystem()->setData(numberOfBoundaryParticles, boundary_beginpos, resolutionX, resolutionY);
	//------------��Ϊ�߽����ӵ����ֻ����һ�Σ����Ե������á�
	solver->BoundarySystem()->boundPointVolunm();
	//auto particle = solver->PBFdata();
	auto particle = solver->sphSystemData();
	auto pos = particle->positions();
	auto boundarypos = solver->BoundarySystem()->BoundaryParticle()->BoundaryPosition();
	Vector2 boundaryTop;
	Vector2 boundaryDown;
	int   BoundaryIndex;
//	auto vel = particle->velocities();
//	auto forces = particle->forces();
      //game loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();                        //����Ƿ����¼�������
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//��ȡ��ǰ֡����ʱ��
		//float currentFrame = glfwGetTime();
		//drawEdge();
		//auto pos = particle->positions();
		for (int i = 0; i < numberOfParticles; i++)
		{
			auto temp = pos->lookAt(i);
			double opengl_X = temp.x()  - 1.0;
			double opengl_Y = temp.y()  - 1.0;
			//cout << opengl_X  << "******" << opengl_Y<< endl;
			TestPoint(opengl_X, opengl_Y);
		}
		//�߽�����
		for (int i = numberOfParticles; i < numberOfAllParticles; i++)
		{
			BoundaryIndex = i - numberOfParticles;
			auto temp = boundarypos->lookAt(BoundaryIndex);
			double opengl_X = temp.x() - 1.0;
			double opengl_Y = temp.y() - 1.0;
			TestBoundaryPoint(opengl_X, opengl_Y);
		}
		auto down = pos->lookAt(numberOfParticles);
		auto top = pos->lookAt(numberOfParticles + numberOfMoveBoundary - 1);
		drawMoveBoundary(down, top);
		glfwSwapBuffers(window);
		boundaryDown = boundarypos->lookAt(0)+ Vector2(-0.06, 0.0);
		boundaryTop = boundarypos->lookAt(numberOfMoveBoundary-1)+Vector2(-0.06,0.0);
		solver->onAdvanceTimeStep(0.018, boundaryTop, boundaryDown);	
		solver->BoundarySystem()->Upadate_Move_Boundary(numberOfMoveBoundary);
	}

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}