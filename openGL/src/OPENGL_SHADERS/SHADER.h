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
	//程序ID
	unsigned int ID;

	//构造器读并构建着色器
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	//使用并激活程序
	void use();
	//uniform 工具函数
	void setBool(const string& name, bool value)const;
	void setInt(const string& name, int value)const;
	void setFloat(const string& name, float value)const;
	void setMat4(const string& name, const glm::mat4& mat)const;
};


#endif 

