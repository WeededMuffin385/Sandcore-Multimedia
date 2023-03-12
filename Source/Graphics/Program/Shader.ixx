module;
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>
#include <fstream>
#include <string>
export module Sandcore.Graphics.Shader;
import Sandcore.Print;

export namespace Sandcore {
	class Shader {
	public:
		enum Type {
			Vertex = GL_VERTEX_SHADER,
			Fragment = GL_FRAGMENT_SHADER,
		};
	public:
		Shader(std::filesystem::path path, Type type) : type(type) {
			if (!std::filesystem::exists(path)) std::print("SHADER DOESN'T EXISTS ON: {}", path.string());
			shader = glCreateShader(type);

			std::ifstream file(path);
			std::string source;
			std::getline(file, source, '\0');
			auto c_str = source.c_str();

			glShaderSource(shader, 1, &c_str, NULL);
			glCompileShader(shader);

			status();
		}

		~Shader() {
			glDeleteShader(shader);
		}

		operator GLuint() {
			return shader;
		}

	private:
		void status() {
			GLint success;
			GLchar infoLog[512];

			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				switch (type) {
				case GL_VERTEX_SHADER:
					std::print("VERTEX SHADER COMPILE ERROR: {}\n", std::string(infoLog));
					break;

				case GL_FRAGMENT_SHADER:
					std::print("FRAGMENT SHADER COMPILE ERROR: {}\n", std::string(infoLog));
					break;
				}
			}
		}
		Type type;
		GLuint shader;
	};
}