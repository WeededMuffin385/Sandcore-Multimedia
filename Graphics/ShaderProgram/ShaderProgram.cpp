#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>
#include <iostream>

import Sandcore.Shader.Program;

import Sandcore.Shader.Object;

namespace Sandcore {
	ShaderProgram::ShaderProgram(std::filesystem::path path) {
		loadFromFile(path);
	}

	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(shaderProgram);
	}

	void ShaderProgram::use() {
		glUseProgram(shaderProgram);
	}

	void ShaderProgram::loadFromFile(std::filesystem::path path) {
		ShaderObject vertexShader(GL_VERTEX_SHADER);
		ShaderObject fragmentShader(GL_FRAGMENT_SHADER);
		vertexShader.loadFromFile(path / "shader.vert");
		fragmentShader.loadFromFile(path / "shader.frag");

		shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		GLint success;
		GLchar infoLog[512];

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
	}

	void ShaderProgram::setInt(std::string title, int value) {
		glUniform1i(glGetUniformLocation(shaderProgram, title.c_str()), value);
	}

	void ShaderProgram::setDouble(std::string title, double value) {
		glUniform1f(glGetUniformLocation(shaderProgram, title.c_str()), value);
	}

	void ShaderProgram::setMat4(std::string title, glm::mat4 value) {
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, title.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
}