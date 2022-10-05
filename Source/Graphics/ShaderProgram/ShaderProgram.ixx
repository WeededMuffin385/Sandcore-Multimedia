#include <glm/glm.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>

export module Sandcore.ShaderProgram;

import Sandcore.Shader;

export namespace Sandcore {
	class ShaderProgram {
	public:
		ShaderProgram(std::filesystem::path path);
		~ShaderProgram();

		void loadFromFile(std::filesystem::path path);

		void use();

		void setInt(std::string title, int value);
		void setdouble(std::string title, double value);
		void setMat4(std::string title, glm::mat4 value);

	private:

		GLuint shaderProgram;
	};
}