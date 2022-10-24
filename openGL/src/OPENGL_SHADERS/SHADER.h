#pragma once
#ifndef SHADER_H
#define SHADER_H

#include<string>

#include<glad/glad.h>
#include<glm/glm.hpp>

using namespace std;

class Shader
{
public:
	//����ID
	unsigned int ID;

	//����������������ɫ��
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	//ʹ�ò��������
	void use();
	//uniform ���ߺ���
	void setBool(const string& name, bool value)const;
	void setInt(const string& name, int value)const;
	void setFloat(const string& name, float value)const;
	void setMat4(const string& name, const glm::mat4& mat)const;
};


#endif 

