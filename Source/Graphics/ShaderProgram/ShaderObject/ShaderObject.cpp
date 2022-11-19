#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

import Sandcore.Shader.Object;

namespace Sandcore{
	
	ShaderObject::ShaderObject(GLenum type) {
		shaderObject = glCreateShader(type);
	}
	

	ShaderObject::~ShaderObject() {
		glDeleteShader(shaderObject);
	}

	ShaderObject::operator GLuint() {
		return shaderObject;
	}
	
	void ShaderObject::loadFromFile(std::filesystem::path path) {
		std::ifstream file(path);
		std::string source;
		std::getline(file, source, '\0');
		const char* c_str = source.c_str();

		glShaderSource(shaderObject, 1, &c_str, NULL);
		glCompileShader(shaderObject);

		GLint success;
		GLchar infoLog[512];

		glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLint type;
			glGetShaderiv(shaderObject, GL_SHADER_TYPE, &type);

			glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);
			switch (type) {
			case GL_VERTEX_SHADER:
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED: ";
				break;

			case GL_FRAGMENT_SHADER:
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: ";
				break;
			}

			std::cout << infoLog << std::endl;
		}
	}
}