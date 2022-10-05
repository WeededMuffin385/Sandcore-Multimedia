#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

import Sandcore.Shader;

namespace Sandcore{
	
	Shader::Shader(GLenum type) {
		shader = glCreateShader(type);
	}
	

	Shader::~Shader() {
		glDeleteShader(shader);
	}

	GLuint Shader::get() {
		return shader;
	}
	
	void Shader::loadFromFile(std::filesystem::path path) {
		std::ifstream file(path);
		std::string source;
		std::getline(file, source, '\0');
		const char* c_str = source.c_str();

		glShaderSource(shader, 1, &c_str, NULL);
		glCompileShader(shader);

		GLint success;
		GLchar infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLint type;
			glGetShaderiv(shader, GL_SHADER_TYPE, &type);

			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			switch (type) {
				case GL_VERTEX_SHADER:{
					std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
					break;
				}

				case GL_FRAGMENT_SHADER: {
					std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
					break;
				}
			}
		}
	}
}