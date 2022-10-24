#include"SHADER.h"
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>

#include<glad/glad.h>

using namespace std;


//使用C++文件流读取着色器的内容，储存在string对象里
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	//1:从文件路径中获取顶点/片段着色器
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;

	//ifstream 对象抛出异常：
	//failbit 表示发生可恢复的错误，badbit表示发生系统性错误
	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	try
	{
		//发生异常
		//1.打开文件
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);


		//2.读取文件的缓冲内容到数据流
		stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();  //将vShaderFile的文件读取到vShaderStream;
		fShaderStream << fShaderFile.rdbuf();

		//3.关闭文件处理器

		vShaderFile.close();
		fShaderFile.close();

         //4.数据流stringstream流到string；
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
        
	}

	catch (ifstream::failure e)
	{
		cout << "ERROR--------SHADER FILE NOT SUCCESFULLY_READ" << endl;

	}

	const char* vShaderCode = vertexCode.c_str();  //.c_str()返回字符串的首字符的指针；
	const char* fShaderCode = fragmentCode.c_str();

//---------------------------以上完成在文件中读取着色器内容--------------------------------------------

//---------------------------编译着色器-----------------------------------------------------------------

	unsigned int vertex, fragment;
	int success;
	char infolog[512];

	//顶点着色器

	vertex = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource函数把要编译的着色器对象作为第一个参数。
	//第二参数指定了传递的源码字符串数量。
	//第三个参数是顶点着色器真正的源码(从文件中读取出来的)
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	//打印编译错误
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infolog);
		cout << "ERROR-----SHADER VERTEX COMPILATION_FAILED\n" << endl;
	}

	//片段着色器

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	//打印编译错误
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infolog);
		cout << "ERROR-----SHADER FRAGMENT COMPILATION_FAILED\n" << infolog<<endl;
	}


	//着色器程序

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	//打印错误信息

	glGetProgramiv(ID, GL_LINK_STATUS, &success);


	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infolog);
		cout << "ERROR-----PROGRAM LINK_FAILED\n" << infolog<<endl;
	}


	//删除着色器
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}


void Shader::use()
{
	glUseProgram(ID);
}




//------------------------以下uniform 函数的setter函数
void Shader::setBool(const string& name, bool value)const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), int(value));


}

void Shader::setInt(const string& name, int value)const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);

}

void Shader::setFloat(const string& name, float value)const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);

}

void Shader::setMat4(const string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

