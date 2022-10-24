#include"SHADER.h"
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>

#include<glad/glad.h>

using namespace std;


//ʹ��C++�ļ�����ȡ��ɫ�������ݣ�������string������
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	//1:���ļ�·���л�ȡ����/Ƭ����ɫ��
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;

	//ifstream �����׳��쳣��
	//failbit ��ʾ�����ɻָ��Ĵ���badbit��ʾ����ϵͳ�Դ���
	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	try
	{
		//�����쳣
		//1.���ļ�
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);


		//2.��ȡ�ļ��Ļ������ݵ�������
		stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();  //��vShaderFile���ļ���ȡ��vShaderStream;
		fShaderStream << fShaderFile.rdbuf();

		//3.�ر��ļ�������

		vShaderFile.close();
		fShaderFile.close();

         //4.������stringstream����string��
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
        
	}

	catch (ifstream::failure e)
	{
		cout << "ERROR--------SHADER FILE NOT SUCCESFULLY_READ" << endl;

	}

	const char* vShaderCode = vertexCode.c_str();  //.c_str()�����ַ��������ַ���ָ�룻
	const char* fShaderCode = fragmentCode.c_str();

//---------------------------����������ļ��ж�ȡ��ɫ������--------------------------------------------

//---------------------------������ɫ��-----------------------------------------------------------------

	unsigned int vertex, fragment;
	int success;
	char infolog[512];

	//������ɫ��

	vertex = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource������Ҫ�������ɫ��������Ϊ��һ��������
	//�ڶ�����ָ���˴��ݵ�Դ���ַ���������
	//�����������Ƕ�����ɫ��������Դ��(���ļ��ж�ȡ������)
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	//��ӡ�������
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infolog);
		cout << "ERROR-----SHADER VERTEX COMPILATION_FAILED\n" << endl;
	}

	//Ƭ����ɫ��

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	//��ӡ�������
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infolog);
		cout << "ERROR-----SHADER FRAGMENT COMPILATION_FAILED\n" << infolog<<endl;
	}


	//��ɫ������

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	//��ӡ������Ϣ

	glGetProgramiv(ID, GL_LINK_STATUS, &success);


	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infolog);
		cout << "ERROR-----PROGRAM LINK_FAILED\n" << infolog<<endl;
	}


	//ɾ����ɫ��
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}


void Shader::use()
{
	glUseProgram(ID);
}




//------------------------����uniform ������setter����
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

