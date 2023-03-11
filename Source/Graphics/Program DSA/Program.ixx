module;
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <filesystem>
#include <fstream>
export module Sandcore.Graphics.Program;

import Sandcore.Graphics.Shader;
import Sandcore.Print;

export namespace Sandcore {
	class Program {
	public:
		Program(std::filesystem::path path) {
			program = glCreateProgram();

			Shader vertShader(path / "shader.vert", Shader::Type::Vertex);
			Shader fragShader(path / "shader.frag", Shader::Type::Fragment);

			glAttachShader(program, vertShader);
			glAttachShader(program, fragShader);
			glLinkProgram(program);

			status();
		}

		~Program() {
			glDeleteProgram(program);
		}

		void status() {
			GLint success;
			GLchar infoLog[512];

			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(program, 512, NULL, infoLog);
				std::print("PROGRAM LINK ERROR: {}", std::string(infoLog));
			}
		}

		void use() {
			glUseProgram(program);
		}

		void setInt(std::string title, int value) {
			glUniform1i(glGetUniformLocation(program, title.c_str()), value);
		}

		void setFloat(std::string title, float value) {
			glUniform1f(glGetUniformLocation(program, title.c_str()), value);
		}

		void setMat4(std::string title, glm::mat4 value) {
			glUniformMatrix4fv(glGetUniformLocation(program, title.c_str()), 1, GL_FALSE, glm::value_ptr(value));
		}

	private:
		GLuint program;
	};
}