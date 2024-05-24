#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

typedef void(*CheckStatus)(GLuint, GLenum, GLint*);
typedef void(*ReadLog)(GLuint, GLsizei, GLsizei*, GLchar*);
#define CheckErrorAndLog(CheckStatus, ReadLog) CheckStatus(obj, checkStatus, &success);if (!success){GLchar InfoLog[1024];ReadLog(obj, 1024, NULL, InfoLog);std::cout << "ERROR::SHADER::PROGRAM_FAILED\n" << InfoLog<< std::endl;}

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath)
	{
		ShaderProgram = glCreateProgram();
		if (ShaderProgram == 0)
		{
			std::cout << "Error creating shader program!" << std::endl;
			exit(-1);
		}
		CompileShaderFromFile(vertexPath, GL_VERTEX_SHADER);
		CompileShaderFromFile(fragmentPath, GL_FRAGMENT_SHADER);
		LinkShaderProgram();
	}
	~Shader()
	{
		glDeleteProgram(ShaderProgram);
	}
	void UseProgram()
	{
		glUseProgram(ShaderProgram);
	}
	void SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ShaderProgram, name.c_str()), value);
	}
	void SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), value);
	}
	void SetVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ShaderProgram, name.c_str()), x, y, z);
	}

private:
	GLuint ShaderProgram;
	void CompileShaderFromFile(const char* path, GLenum shaderType)
	{
		std::string code;
		std::ifstream shaderFile;
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			shaderFile.open(path);
			std::stringstream shaderStream;
			shaderStream << shaderFile.rdbuf();
			shaderFile.close();
			code = shaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
		}
		const GLchar* shaderCode = code.c_str();
		GLuint shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &shaderCode, NULL);
		glCompileShader(shader);
		CheckErrors(shader, "SHADER", GL_COMPILE_STATUS);
		glAttachShader(ShaderProgram, shader);
		glDeleteShader(shader);
	}
	void CheckErrors(GLuint obj, std::string type, int checkStatus )
	{
		GLint success;
		if (type == "SHADER")
		{
			/*
			glGetShaderiv(obj, checkStatus, &success);
			if (!success)
			{
				GLchar InfoLog[1024];
				glGetShaderInfoLog(obj, 1024, NULL, InfoLog);
				std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << InfoLog
					<< std::endl;
				exit(-1);
			}
			*/
			CheckErrorAndLog(glGetShaderiv, glGetShaderInfoLog)
		}
		else if (type == "PROGRAM")
		{
			glGetProgramiv(obj, checkStatus, &success);
			if (!success)
			{
				GLchar InfoLog[1024];
				glGetProgramInfoLog(obj, 1024, NULL, InfoLog);
				std::cout << "ERROR::SHADER::PROGRAM_FAILED\n" << InfoLog
					<< std::endl;
				exit(-1);
			}
		}
	}
	void LinkShaderProgram()
	{
		glLinkProgram(ShaderProgram);
		CheckErrors(ShaderProgram, "PROGRAM", GL_LINK_STATUS);
		glValidateProgram(ShaderProgram);
		CheckErrors(ShaderProgram, "PROGRAM", GL_VALIDATE_STATUS);
	}
};